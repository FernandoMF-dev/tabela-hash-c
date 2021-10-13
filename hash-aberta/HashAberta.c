#include "headers/HashAberta.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_INVALID_LENGTH "\n\tERRO: Não e possível criar uma HASH com menos de 1 índice!\n"

#define MAX_LIST_LABEL_LENGTH 7

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int hashFunction(HashAberta *hash, char *key);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

int hashFunction(HashAberta *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=
