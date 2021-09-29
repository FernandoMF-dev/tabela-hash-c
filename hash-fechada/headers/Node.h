#include <stdio.h>
#include <stdlib.h>

#ifndef HASH_FECHADA_NODE_H
#define HASH_FECHADA_NODE_H

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    int elemen;
} Node;

Node *newNode(int value);

void printNode(Node *node);

int compareNodeByKey(Node *node, int key);

#endif //HASH_FECHADA_NODE_H
