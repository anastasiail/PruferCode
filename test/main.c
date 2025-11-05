#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/graph.h"

int main() {
    srand(time(NULL));

    int n1 = 5;
    int code1[] = {1, 1, 4};
    
    G tree1 = pruferToTree(code1, n1);
    printf("Из кода {1, 1, 4} (n=5):\n");
    printTree(tree1, n1);
    freeGraph(tree1, n1);
    printf("\n");

    int n2 = 7;
    
    G tree2 = generateRandomTree(n2);
    printTree(tree2, n2);
    freeGraph(tree2, n2);
    printf("\n");

    printf("Особый случай n=2: \n");
    int n3 = 2;
    G tree3 = generateRandomTree(n3);
    printTree(tree3, n3);
    freeGraph(tree3, n3);
    printf("\n");

    printf("Для n=1: \n");
    int n4 = 1;
    G tree4 = generateRandomTree(n4);
    printTree(tree4, n4);
    freeGraph(tree4, n4);
    printf("\n");
    
    printf("Для n=0: \n");
    int n5 = 0;
    G tree5 = generateRandomTree(n5);
    printTree(tree5, n5);
    freeGraph(tree5, n5);
    printf("\n");
    
    printf("Большое дерево (n=10): \n");
    int n6 = 10;
    G tree6 = generateRandomTree(n6);
    printTree(tree6, n6);
    freeGraph(tree6, n6);
    printf("\n");
    
    printf("Большое дерево (n=50): \n");
    int n7 = 50;
    G tree7 = generateRandomTree(n7);
    printTree(tree7, n7);
    freeGraph(tree7, n7);
    printf("\n");

    return 0;
}