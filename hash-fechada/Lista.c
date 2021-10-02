#include "headers/Lista.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERRO_LISTA_VAZIA "\n\tERRO: A lista está vazia!\n"
#define ERRO_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado\n"
#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

#define TRUE 1
#define FALSE 0

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int insertEmpty(List *list, Aluno value);

int insertFirst(List *list, Aluno value);

int insertLast(List *list, Aluno value);

int insertMiddle(List *list, Aluno value);

void removeFirst(List *list);

void removeLast(List *list);

void removeMiddle(List *list, char *key);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

int insertEmpty(List *list, Aluno value) {
    Node *node = newNode(value);
    if (node == NULL) {
        return FALSE;
    }

    list->first = node;
    list->last = node;

    return TRUE;
}

int insertFirst(List *list, Aluno value) {
    Node *node = newNode(value);
    if (node == NULL) {
        return FALSE;
    }

    node->next = list->first;
    list->first->prev = node;
    list->first = node;

    return TRUE;
}

int insertLast(List *list, Aluno value) {
    Node *node = newNode(value);
    if (node == NULL) {
        return FALSE;
    }

    node->prev = list->last;
    list->last->next = node;
    list->last = node;

    return TRUE;
}

int insertMiddle(List *list, Aluno value) {
    Node *node = newNode(value);
    if (node == NULL) {
        return FALSE;
    }

    Node *aux = list->first;
    while (compareAluno(aux->value, node->value) < 0) {
        aux = aux->next;
    }

    node->next = aux;
    node->prev = aux->prev;
    aux->prev->next = node;
    aux->prev = node;

    return TRUE;
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

void removeMiddle(List *list, char *key) {
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

    if (list == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    list->label = label;

    return list;
}

void insertList(List *list, Aluno value) {
    int success;

    if (list->size == 0) {
        success = insertEmpty(list, value);
    } else if (compareAluno(list->first->value, value) > 0) {
        success = insertFirst(list, value);
    } else if (compareAluno(list->first->value, value) < 0) {
        success = insertLast(list, value);
    } else {
        success = insertMiddle(list, value);
    }

    if (success) {
        list->size++;
    }
}

Aluno searchList(List *list, char *key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
        return newAluno();
    }

    Node *node = list->first;
    int compare = compareNodeByKey(node, key);

    while (node != NULL && compare < 0) {
        node = node->next;
        compare = compareNodeByKey(node, key);
    }

    if (compare == 0) {
        return node->value;
    }

    printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    return newAluno();
}

void removeList(List *list, char *key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
    }

    if (list->size == 1 && compareNodeByKey(list->first, key) == 0) {
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
        insertList(target, node->value);
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