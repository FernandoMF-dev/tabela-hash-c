#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

#ifndef HASH_FECHADA_LISTA_H
#define HASH_FECHADA_LISTA_H

typedef struct List {
    char *label;
    int size;
    Node *first;
    Node *last;
} List;

List *newList(char *label);

void insertList(List *list, int value);

int searchList(List *list, int key);

void removeList(List *list, int key);

void clearList(List *list);

void cloneList(List *target, List *source);

void printList(List *list);

#endif //HASH_FECHADA_LISTA_H
