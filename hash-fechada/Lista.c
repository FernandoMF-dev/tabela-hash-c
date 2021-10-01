#include "headers/Lista.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERRO_LISTA_VAZIA "\n\tERRO: A lista está vazia!\n"
#define ERRO_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado\n"

// =-=-=-=-= METODOS PRIVADOS =-=-=-=-=

void insertEmpty(List *list, int value) {
    Node *node = newNode(value);
    list->first = node;
    list->last = node;
}

void insertFirst(List *list, int value) {
    Node *node = newNode(value);
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
}

void insertLast(List *list, int value) {
    Node *node = newNode(value);
    node->prev = list->last;
    list->last->next = node;
    list->last = node;
}

void insertMiddle(List *list, int value) {
    Node *node = newNode(value);
    Node *aux = list->first;

    while (aux->elemen < node->elemen) {
        aux = aux->next;
    }

    node->next = aux;
    node->prev = aux->prev;
    aux->prev->next = node;
    aux->prev = node;
}

void removeFirst(List *list) {
    Node *node = list->first;
    Node *next = node->next;

    next->prev = NULL;
    node->next = NULL;
    list->first = next;
    free(node);
    list->size--;
}

void removeLast(List *list) {
    Node *node = list->last;
    Node *prev = node->prev;

    prev->next = NULL;
    list->last = prev;
    free(node);
    list->size--;
}

void removeMiddle(List *list, int key) {
    Node *node = list->first;
    int exists = compareNodeByKey(node, key);

    while (node != NULL && exists < 0) {
        node = node->next;
        exists = compareNodeByKey(node, key);
    }

    if (exists > 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    Node *prev = node->prev;
    Node *next = node->next;

    next->prev = prev;
    prev->next = next;
    node->prev = NULL;
    node->next = NULL;
    free(node);
    list->size--;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

List *newList(char *label) {
    List *list = (List *) malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    list->label = label;
    return list;
}

void insertList(List *list, int value) {
    if (list->size == 0) {
        insertEmpty(list, value);
    } else if (list->first->elemen > value) {
        insertFirst(list, value);
    } else if (list->last->elemen < value) {
        insertLast(list, value);
    } else {
        insertMiddle(list, value);
    }
    list->size++;
}

int searchList(List *list, int key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
        return NULL;
    }

    Node *node = list->first;
    int compare = compareNodeByKey(node, key);

    while (node != NULL && compare < 0) {
        node = node->next;
        compare = compareNodeByKey(node, key);
    }

    if (compare == 0) {
        return node->elemen;
    }

    printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    return NULL;
}

void removeList(List *list, int key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
    }

    if (list->size == 1 && compareNodeByKey(list->first, key)) {
        return clearList(list);
    }
    if (compareNodeByKey(list->first, key) == 0) {
        return removeFirst(list);
    }
    if (compareNodeByKey(list->last, key) == 0) {
        return removeLast(list);
    }
    removeMiddle(list, key);
}

void clearList(List *list) {
    if (list->size > 1) {
        free(list->first);
        free(list->last);
    } else {
        free(list->first);
    }

    list->size = 0;
    list->first = NULL;
    list->last = NULL;
}

void cloneList(List *target, List *source) {
    Node *node = source->first;
    clearList(target);

    while (node != NULL) {
        insertList(target, node->elemen);
        node = node->next;
    }
}

void printList(List *list) {
    Node *node = list->first;

    printf("\n%s[ ", list->label);
    while (node != NULL) {
        printNode(node);
        node = node->next;
        if (node != NULL) {
            printf(", ");
        }
    }
    printf(" ]");
}