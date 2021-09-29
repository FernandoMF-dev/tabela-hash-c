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

void push(List *list, int value);

int listSearch(List *list, int key);

void pop(List *list, int key);

void cleanList(List *list);

void cloneList(List *target, List *source);

void printList(List *list);

#endif //HASH_FECHADA_LISTA_H
