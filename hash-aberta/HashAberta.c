#include "headers/HashAberta.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"
#define ERROR_INVALID_LENGTH "\n\tERRO: Não e possível criar uma HASH com menos de 1 índice!\n"

#define EXPANSAO_MULTIPLICADOR 2

#define STATUS_APAGADO -1
#define STATUS_VAZIO 0
#define STATUS_OCUPADO 1

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int hashFunction(HashAberta *hash, char *key);

int compareNodeByKey(Node *node, char *key);

Node *newNode(int index);

Node **createNodeSequence(int length);

HashAberta *expandsHash(HashAberta *source);

int regulateHashIndex(HashAberta *base, int index);

int verifyContinueSearch(Node *node, int counter, int hashLength);

int findInitialBlockIndex(HashAberta *hash);

Node *getNode(HashAberta *hash, int index);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

/*
 * Retorna o índice da hash que um registro deve ser inserido de acordo com uma chave
 * */
int hashFunction(HashAberta *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

/*
 * Compara se uma chave (key) corresponde ao valor de um Node.
 *
 * Se sim, retorna 1.
 * Se não, retorna 0.
 * */
int compareNodeByKey(Node *node, char *key) {
    return node->status == STATUS_OCUPADO && compareAlunoByKey(node->value, key) == 0;
}

/*
 * Inicializa e retorna uma nova intância de Node.
 * */
Node *newNode(int index) {
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    node->index = index;
    node->status = STATUS_VAZIO;
    node->value = NULL;
    node->next = NULL;

    return node;
}

/*
 * Inicializa e retorna uma lista de acordo com o tamanho da Hash passado
 * */
Node **createNodeSequence(int length) {
    if (length < 1) {
        return NULL;
    }

    Node **sequence = (Node **) malloc(length * sizeof(Node *));

    if (sequence == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    sequence[0] = newNode(0);
    Node *aux;

    for (int i = 1; i < length; ++i) {
        aux = newNode(i);
        sequence[i - 1]->next = aux;
        sequence[i] = aux;
    }
    sequence[length - 1]->next = sequence[0];

    return sequence;
}

/*
 * Expande a quantidade de elementos que cabem numa Hash
 * */
HashAberta *expandsHash(HashAberta *source) {
    HashAberta *target = newHashAberta(source->label, source->length * EXPANSAO_MULTIPLICADOR, source->chargeFactor);

    cloneHash(target, source);

    free(source->elements);
    free(source);
    return target;
}

/*
 * Verifica e retorna a qual índice da Hash o valor de 'index' corresponde.
 * */
int regulateHashIndex(HashAberta *base, int index) {
    while (index < 0) {
        index += base->length;
    }

    return index % base->length;
}

/*
 * Verifica se o ator deve continuar percorrendo os valores uma Hash.
 *
 * Se sim, retorna 1.
 * Se não, retorna 0.
 * */
int verifyContinueSearch(Node *node, int counter, int hashLength) {
    return node->status != STATUS_VAZIO && counter < hashLength;
}

/*
 * Busca e retorna o índice de início do primeiro bloco de uma Hash
 * */
int findInitialBlockIndex(HashAberta *hash) {
    int index = 0;

    while (verifyContinueSearch(getNode(hash, index - 1), index, hash->length)) {
        index++;
    }

    return index;
}

/*
 * Retorna o Node da Hash correspondente ao índice especificado.
 * */
Node *getNode(HashAberta *hash, int index) {
    return hash->elements[regulateHashIndex(hash, index)];
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Inicializa e retorna uma nova instância de Hash.
 * */
HashAberta *newHashAberta(char *label, int length, double chargeFactor) {
    if (length <= 1) {
        printf(ERROR_INVALID_LENGTH);
        return NULL;
    }

    HashAberta *hash = (HashAberta *) malloc(sizeof(HashAberta));

    if (hash == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    hash->label = label;
    hash->length = length;
    hash->chargeFactor = chargeFactor;
    hash->size = 0;
    hash->elements = createNodeSequence(hash->length);

    if (hash->elements == NULL) {
        return NULL;
    }

    return hash;
}

/*
 * Insere um novo registro numa Hash.
 * */
HashAberta *insertHash(HashAberta *hash, Aluno *value) {
    if ((double) hash->size / (double) hash->length > hash->chargeFactor) {
        hash = expandsHash(hash);
    }

    int index = hashFunction(hash, value->matricula);
    Node *node = hash->elements[index];

    while (node->status == STATUS_OCUPADO) {
        node = node->next;
    }

    node->status = STATUS_OCUPADO;
    node->value = value;
    hash->size++;

    return hash;
}

/*
 * Busca um registro na Hash de acordo com uma chave.
 *
 * Se encontrar, retorna os dados do registro.
 * Se não, retorna NULL.
 * */
Aluno *searchHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];
    int counter = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        if (compareNodeByKey(node, key)) {
            return node->value;
        }
        node = node->next;
        counter++;
    }
    printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    return NULL;
}

/*
 * Busca um registro na Hash e imprime os seguintes dados sobre ele:
 *
 * - Índice da Hash em que ele se localiza;
 * - Os dados do registro;
 * - O número de registros que foram veríficados antes do alvo ser encontrado.
 * */
void findAndPrintHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];
    int counter = 0;
    int found = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        if (compareNodeByKey(node, key)) {
            found = 1;
            break;
        }
        node = node->next;
        counter++;
    }

    if (found) {
        printf("\nO registro foi encontrado no índice %d\n", node->index);
        printAluno(node->value);
    } else {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    }
    printf("\nForam comparados %d registros antes de encontrar esse resultado", counter);
}

/*
 * Remove um registro da Hash de acordo com uma chave.
 * */
void removeHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];
    int counter = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        if (compareNodeByKey(node, key)) {
            node->status = STATUS_APAGADO;
            free(node->value);
            hash->size--;
            return;
        }
        node = node->next;
        counter++;
    }
    printf(ERROR_REGISTRO_NAO_ENCONTRADO);
}

/*
 * Remove todos os registros da Hash.
 * */
void clearHash(HashAberta *hash) {
    Node *node = hash->elements[0];

    do {
        if (node->status != STATUS_VAZIO) {
            if (node->status == STATUS_OCUPADO) {
                free(node->value);
            }
            node->status = STATUS_VAZIO;
        }
        node = node->next;
    } while (node->index != 0);
    hash->size = 0;
}

/*
 * Lê todos os registros da Hash 'source' e os insere na Hash 'target'.
 * */
void cloneHash(HashAberta *target, HashAberta *source) {
    Node *node = source->elements[0];

    clearHash(target);
    do {
        if (node->status == STATUS_OCUPADO) {
            insertHash(target, node->value);
        }
        node = node->next;
    } while (node->index != 0);
}

/*
 * Imprime uma Hash.
 * */
void printHash(HashAberta *hash) {
    int counter = 0;

    printf("%s(%d/%d)[ ", hash->label, hash->size, hash->length);
    for (int i = 0; i < hash->length; ++i) {
        if (hash->elements[i]->status == STATUS_OCUPADO) {
            printAluno(hash->elements[i]->value);
            counter++;
            if (counter >= hash->size) {
                break;
            }
            printf(", ");
        }
    }
    printf(" ]");
}

/*
 * Imprime um bloco de uma Hash.
 * */
void printBlockHash(HashAberta *hash, int block) {
    Node *node = getNode(hash, block);
    int alreadyPrinted = 0;
    int counter = 0;

    printf("(%d)[ ", blockLengthHash(hash, block));
    while (verifyContinueSearch(node, counter, hash->length)) {
        if (alreadyPrinted) {
            printf(", ");
        }

        if (node->status == STATUS_OCUPADO) {
            printAluno(node->value);
        } else {
            printf("{}");
        }

        alreadyPrinted = 1;
        node = node->next;
        counter++;
    }
    printf(" ]");
}

/*
 * Retorna o tamanho de um bloco da Hash.
 * */
int blockLengthHash(HashAberta *hash, int block) {
    Node *node = getNode(hash, block);
    int length = 0;
    int counter = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        node = node->next;
        length++;
        counter++;
    }

    return length;
}

/*
 * Retorna a quantidade de blocos diferentes na Hash.
 * */
int numberOfBlocksHash(HashAberta *hash) {
    int initialIndex = findInitialBlockIndex(hash);
    int index = initialIndex;
    int blocks = 0;
    int length;

    while (index < hash->length + initialIndex) {
        length = blockLengthHash(hash, index);
        if (length > 0) {
            blocks++;
        }
        index += length + 1;
    }

    return blocks;
}

/*
 * Retorna o tamanho médio dos blocos da Hash.
 * */
double averageBlockLengthHash(HashAberta *hash) {
    int initialIndex = findInitialBlockIndex(hash);
    int index = initialIndex;
    int blocks = 0;
    double averageLength = 0.0;
    int length;

    while (index < hash->length + initialIndex) {
        length = blockLengthHash(hash, index);
        if (length > 0) {
            averageLength += (double) length;
            blocks++;
        }
        index += length + 1;
    }

    if (blocks == 0) {
        return 0;
    }
    return averageLength / (double) blocks;
}

/*
 * Retorna o índice do menor bloco de uma Hash.
 * */
int shortestBlockHash(HashAberta *hash) {
    int initialIndex = findInitialBlockIndex(hash);
    int shortestIndex = initialIndex;
    int shortestLength = blockLengthHash(hash, shortestIndex);
    int index = shortestLength + initialIndex + 1;
    int length;

    while (index < hash->length + initialIndex) {
        length = blockLengthHash(hash, index);
        if (length > 0 && (shortestLength == 0 || length < shortestLength)) {
            shortestLength = length;
            shortestIndex = index;
        }
        index += length + 1;
    }

    return regulateHashIndex(hash, shortestIndex);
}

/*
 * Retorna o índice do maior bloco de uma Hash.
 * */
int longestBlockHash(HashAberta *hash) {
    int longestIndex = 0;
    int longestLength = blockLengthHash(hash, longestIndex);
    int index = longestLength + 1;
    int length;

    while (index < hash->length) {
        length = blockLengthHash(hash, index);
        if (length > longestLength) {
            longestLength = length;
            longestIndex = index;
        }
        index += length + 1;
    }

    return regulateHashIndex(hash, longestIndex);
}

/*
 * Imprime os seguintes dados de uma Hash:
 *
 * - Nome;
 * - Número de blocos;
 * - Números de registros na hash;
 * - Tamanho médio dos blocos da hash;
 * - Índice do menor bloco e a quantidades de registros nele;
 * - Índice do maior bloco e a quantidades de registros nele.
 * */
void printStatisticsHash(HashAberta *hash) {
    double averageBlockLength = averageBlockLengthHash(hash);
    int shortestBlockIndex = shortestBlockHash(hash);
    int longestBlockIndex = longestBlockHash(hash);
    int blocks = numberOfBlocksHash(hash);

    printf("\n-> %s", hash->label);
    printf("\n-> Número total de blocos: %d", blocks);
    printf("\n-> Número total de registros na hash: %d", hash->size);
    printf("\n-> Média do tamanho dos blocos: %.3lf", averageBlockLength);
    printf("\n-> Bloco mais curto: %d (%d registro(s))", shortestBlockIndex, blockLengthHash(hash, shortestBlockIndex));
    printf("\n-> Bloco mais longo: %d (%d registro(s))", longestBlockIndex, blockLengthHash(hash, longestBlockIndex));
}