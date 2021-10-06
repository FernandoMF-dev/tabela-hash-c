#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
#include "Aluno.h"

#ifndef HASH_FECHADA_LISTA_H
#define HASH_FECHADA_LISTA_H

typedef struct List {
    char *label;
    int size;
    Node *first;
    Node *last;
} List;

List *newList(char *label);

void insertList(List *list, Aluno *value);

Aluno *searchList(List *list, char *key);

void removeList(List *list, char *key);

void clearList(List *list);

void cloneList(List *target, List *source);

void printList(List *list);

void findAndPrintList(List *list, char *key);

#endif //HASH_FECHADA_LISTA_H
