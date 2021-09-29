#include "headers/Node.h"

Node *newNode(int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->elemen = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void printNode(Node *node) {
    printf("%d", node->elemen);
}

int compareByKey(Node *node, int key) {
    if (node == NULL) {
        return 2;
    }

    int element = node->elemen;

    if (element < key) {
        return -1;
    }
    if (element > key) {
        return 1;
    }
    if (element == key) {
        return 0;
    }

}