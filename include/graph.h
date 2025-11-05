#ifndef GRAPH_H
#define GRAPH_H

// Узел для списка смежности
struct E_i {
    int dest; // Куда ведёт ребро (номер вершины)
    struct E_i* next; // Следующий сосед
};

typedef struct E_i** G; // Массив указателей на списки соседей

// Функции для работы с графами
void addEdge(G E_lists, int from, int to);
void freeGraph(G E_lists, int n);
void printTree(G E_lists, int n);
G pruferToTree(int* PCode, int n);
G generateRandomTree(int n);

#endif