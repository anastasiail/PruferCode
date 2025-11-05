#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/graph.h"

void addEdge(G E_lists, int from, int to) {
    // Ребро из from в to
    struct E_i* newNodeTo = (struct E_i*)malloc(sizeof(struct E_i));
    newNodeTo->dest = to;
    newNodeTo->next = E_lists[from];
    E_lists[from] = newNodeTo;

    // Ребро из to в from
    struct E_i* newNodeFrom = (struct E_i*)malloc(sizeof(struct E_i));
    newNodeFrom->dest = from;
    newNodeFrom->next = E_lists[to];
    E_lists[to] = newNodeFrom;
}

void freeGraph(G E_lists, int n) {
    if (E_lists == NULL) return;

    for (int i = 1; i <= n; i++) {
        struct E_i* current = E_lists[i];
        // Идем по списку соседей и удаляем каждый узел для всех вершин
        while (current != NULL) {
            struct E_i* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(E_lists);
}

void printTree(G E_lists, int n) {
    if (E_lists == NULL) {
        printf("Дерево пустое (n < 2)\n");
        return;
    }
    printf("Списки смежности для дерева (n=%d):\n", n);
    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);
        struct E_i* current = E_lists[i];
        if (current == NULL) {
            printf("лист");
        }
        while (current != NULL) {
            printf("%d ", current->dest);
            current = current->next;
        }
        printf("\n");
    }
}

G pruferToTree(int* PCode, int n) {
    // В коде Прюфера n-2 элемента
    if (n < 2) return NULL;

    int m = n - 2;

    int* deg = (int*)calloc(n + 1, sizeof(int)); // Массив для степеней вершин

    for (int i = 0; i < m; i++) {
        deg[PCode[i]]++; // Считаем вхождения вершин в код
    }

    for (int i = 1; i <= n; i++) {
        deg[i]++; // +1 для каждой вершины так как степень вершины = (сколько раз встречается в коде) + 1
    }

    G E_lists = (G)calloc(n + 1, sizeof(struct E_i*)); // Создаём пустой граф

    for (int i = 0; i < m; i++) {
        // Находим наименьшую вершину v со степенью 1
        int v = 0;
        for (int j = 1; j <= n; j++) {
            if (deg[j] == 1) {
                v = j;
                break;
            }
        }
        
        int u = PCode[i];
        
        addEdge(E_lists, u, v); // Добавляем ребро
        
        // Уменьшаем степени
        deg[u]--;
        deg[v]--;
    }

    // Последнее ребро
    int u = 0, v = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            if (u == 0) {
                u = i;
            } else {
                v = i;
                break;
            }
        }
    }
    
    // При n = 2
    if (u != 0 && v != 0) {
        addEdge(E_lists, u, v);
    }

    free(deg);

    return E_lists;
}

G generateRandomTree(int n) {
    if (n < 2) return NULL;

    int m = n - 2;
    int* PCode = NULL;

    // Случайный код Прюфера
    if (m > 0) {
        PCode = (int*)malloc(m * sizeof(int));
        
        for (int i = 0; i < m; i++) {
            PCode[i] = (rand() % n) + 1; // +1 чтобы было от 1 до n
        }
    }

    G tree = pruferToTree(PCode, n); // Восстанавливаем дерево

    if (PCode != NULL) {
        free(PCode);
    }

    return tree;
}