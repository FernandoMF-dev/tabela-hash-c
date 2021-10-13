#include "headers/HashFechada.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_INVALID_LENGTH "\n\tERRO: Não e possível criar uma HASH com menos de 1 índice!\n"

#define MAX_LIST_LABEL_LENGTH 7

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int hashFunction(HashFechada *hash, char *key);

List *initializeElementList(int i);

List **initializeElements(int length);

void printHashName(HashFechada *hash);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

/*
 * Retorna o índice da hash que um registro deve ser inserido de acordo com uma chave
 * */
int hashFunction(HashFechada *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

/*
 * Inicializa e retorna uma lista de acordo com o índice da Hash passado
 * */
List *initializeElementList(int i) {
    List *list = newList("");
    if (list == NULL) {
        return NULL;
    }

    list->label = (char *) malloc((MAX_LIST_LABEL_LENGTH + 1) * sizeof(char));
    sprintf(list->label, "%d", i);

    return list;
}

/*
 * Inicializa e retorna as listas para cada índice da Hash
 * */
List **initializeElements(int length) {
    List **elements = (List **) malloc(length * sizeof(List *));

    for (int i = 0; i < length; i++) {
        elements[i] = initializeElementList(i);
        if (elements[i] == NULL) {
            return NULL;
        }
    }

    return elements;
}

/*
 * Imprime o nome de uma da hash, se existir
 * */
void printHashName(HashFechada *hash) {
    if (strlen(hash->label)) {
        printf("\n%s:", hash->label);
    }
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Inicializa e retorna uma nova instância de Hash
 * */
HashFechada *newHashFechada(char *label, int length) {
    if (length < 1) {
        printf(ERROR_INVALID_LENGTH);
        return NULL;
    }

    HashFechada *hash = (HashFechada *) malloc(sizeof(HashFechada));

    if (hash == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    hash->label = label;
    hash->length = length;
    hash->elements = initializeElements(length);

    if (hash->elements == NULL) {
        return NULL;
    }

    return hash;
}

/*
 * Insere um novo registro numa Hash
 * */
void insertHash(HashFechada *hash, Aluno *value) {
    int index = hashFunction(hash, value->matricula);
    insertList(hash->elements[index], value);
}

/*
 * Busca um registro na Hash de acordo com uma chave
 *
 * Se encontrar, retorna os dados do registro.
 * Se não, retorna NULL
 * */
Aluno *searchHash(HashFechada *hash, char *key) {
    int index = hashFunction(hash, key);
    return searchList(hash->elements[index], key);
}

/*
 * Busca um registro na Hash e imprime os seguintes dados sobre ele:
 *
 * - Índice da Hash em que ele se localiza;
 * - Os dados do registro;
 * - O número de registros que foram veríficados antes do alvo ser encontrado;
 * */
void findAndPrintHash(HashFechada *hash, char *key) {
    int index = hashFunction(hash, key);
    printHashName(hash);
    printf("\nIndex: %d", index);
    findAndPrintList(hash->elements[index], key);
}

/*
 * Remove um registro da Hash de acordo com uma chave
 * */
void removeHash(HashFechada *hash, char *key) {
    int index = hashFunction(hash, key);
    removeList(hash->elements[index], key);
}

/*
 * Remove todos os registros da Hash
 * */
void clearHash(HashFechada *hash) {
    for (int i = 0; i < hash->length; i++) {
        clearList(hash->elements[i]);
    }
}

/*
 * Copia os registros da Hash 'source' para a Hash 'target'
 * */
void cloneHash(HashFechada *target, HashFechada *source) {
    clearHash(target);
    free(target->elements);
    target->length = source->length;
    target->elements = initializeElements(target->length);
    for (int i = 0; i < target->length; i++) {
        cloneList(target->elements[i], source->elements[i]);
    }
}

/*
 * Imprimi uma struct Hash
 * */
void printHash(HashFechada *hash) {
    if (strlen(hash->label)) {
        printf("\n%s:", hash->label);
    }
    for (int i = 0; i < hash->length; i++) {
        printList(hash->elements[i]);
    }
}

/*
 * Retorna o número de registros numa Hash
 * */
int sizeHash(HashFechada *hash) {
    int size = 0;

    for (int i = 0; i < hash->length; i++) {
        size += hash->elements[i]->size;
    }

    return size;
}

/*
 * Retorna a média de números de registros por índice de uma Hash
 * */
double averageNodesPerListHash(HashFechada *hash) {
    return (double) sizeHash(hash) / (double) hash->length;
}

/*
 * Retorna o índice com menos registros de uma Hash
 * */
int shortestListHash(HashFechada *hash) {
    int size = hash->elements[0]->size;
    int index = 0;

    for (int i = 1; i < hash->length; i++) {
        if (hash->elements[i]->size < size) {
            size = hash->elements[i]->size;
            index = i;
        }
    }

    return index;
}

/*
 * Retorna o índice com mais registros de uma Hash
 * */
int longestListHash(HashFechada *hash) {
    int size = hash->elements[0]->size;
    int index = 0;

    for (int i = 1; i < hash->length; i++) {
        if (hash->elements[i]->size > size) {
            size = hash->elements[i]->size;
            index = i;
        }
    }

    return index;
}

/*
 * Retorna o desvio-padrão dos números de registros por índice de uma Hash
 * */
double standardDeviationHash(HashFechada *hash) {
    double standardDeviation = 0;
    double average = averageNodesPerListHash(hash);

    for (int i = 0; i < hash->length; i++) {
        standardDeviation += pow((double) (hash->elements[i]->size - average), 2);
    }

    return pow(standardDeviation / sizeHash(hash), 0.5);
}

/*
 * Retorna a quantidade de índices cujo número de registros estejam dentro do intervalo da média mais/menos o desvio padrão
 * */
int countListsNormalDistribution(HashFechada *hash) {
    double average = averageNodesPerListHash(hash);
    double standardDeviation = standardDeviationHash(hash);
    double size;
    int count = 0;

    for (int i = 0; i < hash->length; i++) {
        size = (double) hash->elements[i]->size;
        if (size >= (average - standardDeviation) && size <= (average + standardDeviation)) {
            count++;
        }
    }

    return count;
}

/*
 * Imprime os seguintes dados de uma Hash:
 *
 * - Nome;
 * - Número de registros;
 * - Média de números de registros por índice;
 * - Índice com mais registros e a quantidades de registros nele;
 * - Índice com menos registros e a quantidades de registros nele;
 * - Desvio-padrão dos números de registros por índice;
 * - Quantidade de índices cujo número de registros estejam dentro do intervalo da média mais/menos o desvio padrão.
 * */
void printStatisticHash(HashFechada *hash) {
    int longestIndex = longestListHash(hash);
    int shortestIndex = shortestListHash(hash);

    printHashName(hash);
    printf("\nQuantidade total de registros: %d", sizeHash(hash));
    printf("\nMédia de registros por índice: %.2lf", averageNodesPerListHash(hash));
    printf("\nÍndice mais longo: %d (%d registro(s))", longestIndex, hash->elements[longestIndex]->size);
    printf("\nÍndice mais curto: %d (%d registro(s))", shortestIndex, hash->elements[shortestIndex]->size);
    printf("\nDesvio padrão da quantidade de registros pelos índices: %.2lf", standardDeviationHash(hash));
    printf("\nQuantidade dentro do intervalo da média +/- o desvio padrão: %d", countListsNormalDistribution(hash));
}