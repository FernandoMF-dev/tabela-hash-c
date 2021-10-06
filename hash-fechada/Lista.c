#include "headers/Lista.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERRO_LISTA_VAZIA "\n\tERRO: A lista está vazia!\n"
#define ERRO_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado\n"
#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

#define TRUE 1
#define FALSE 0

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int insertBegin(List *list, Aluno *value);

int insertEnd(List *list, Aluno *value);

void removeBegin(List *list);

void removeAnywhere(List *list, char *key);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

int insertBegin(List *list, Aluno *value) {
    Node *node = newNode(value);
    if (node == NULL) {
        return FALSE;
    }

    list->first = node;
    list->last = node;

    return TRUE;
}

int insertEnd(List *list, Aluno *value) {
    Node *node = newNode(value);
    if (node == NULL) {
        return FALSE;
    }

    list->last->next = node;
    list->last = node;

    return TRUE;
}

void removeBegin(List *list) {
    Node *node = list->first;
    Node *next = node->next;

    node->next = NULL;
    list->first = next;
    free(node);
    list->size--;
}

void removeAnywhere(List *list, char *key) {
    Node *prev = list->first;
    Node *node = prev->next;
    int exists = compareNodeByKey(node, key);

    while (node != NULL && exists != 0) {
        prev = prev->next;
        node = prev->next;
        exists = compareNodeByKey(node, key);
    }

    if (exists != 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    prev->next = node->next;
    if (prev->next == NULL) {
        list->last = prev;
    }
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

void insertList(List *list, Aluno *value) {
    int success;

    if (list->size == 0) {
        success = insertBegin(list, value);
    } else {
        success = insertEnd(list, value);
    }

    if (success) {
        list->size++;
    }
}

Aluno *searchList(List *list, char *key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
        return newAluno();
    }

    Node *node = list->first;
    int compare = compareNodeByKey(node, key);

    while (node != NULL && compare != 0) {
        node = node->next;
        compare = compareNodeByKey(node, key);
    }

    if (compare == 0) {
        return node->value;
    }
    printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    return newAluno();
}

void findAndPrintList(List *list, char *key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
        return;
    }

    Node *node = list->first;
    int verifications = 0;
    int compare = compareNodeByKey(node, key);

    while (node != NULL && compare != 0) {
        node = node->next;
        compare = compareNodeByKey(node, key);
        verifications++;
    }

    printf("\n");
    if (compare != 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    } else {
        printNode(node);
    }
    printf("\n%d registros verificados antes desse.\n", verifications);
}

void removeList(List *list, char *key) {
    if (list->size == 0) {
        printf(ERRO_LISTA_VAZIA);
        return;
    }
    if (compareNodeByKey(list->first, key) == 0) {
        if (list->size == 1) {
            return clearList(list);
        }
        return removeBegin(list);
    }
    removeAnywhere(list, key);
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