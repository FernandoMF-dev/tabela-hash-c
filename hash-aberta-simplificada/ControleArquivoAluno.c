#include "headers/ControleArquivoAluno.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERRO_ABRIR_ARQUIVO "\n\tERRO: Erro na abertura do arquivo!\n"

#define MENSSAGE_LENDO_ARQUIVO "\n\tAVISO: Lendo arquivo, por favor aguarde...\n"
#define MENSSAGE_SALVANDO_ARQUIVO "\n\tAVISO: Salvando arquivo, por favor aguarde...\n"

#define DIRETORIO_ARQUIVO_ENTRADA "./entrada/entrada.txt"
#define DIRETORIO_ARQUIVO_SAIDA "./saida/"

#define LINE_MAX_LENGTH 255
#define FILE_NAME_MAX_LENGTH 31
#define DELIMITER ";"

#define STATUS_OCUPADO 1

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

Aluno *readNextAluno(FILE *fp);

void writeAlunosOnFile(FILE *fp, HashAberta *hash);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

/*
 * Lê a próxima linha do arquivo e preencha dados de Aluno
 * */
Aluno *readNextAluno(FILE *fp) {
    Aluno *aluno = newAluno();
    char *line = (char *) malloc((LINE_MAX_LENGTH + 1) * sizeof(char));
    char *ptr;

    fscanf(fp, " %[^\n]%*c", line);
    ptr = strtok(line, DELIMITER);
    strcpy(aluno->matricula, ptr);

    ptr = strtok(NULL, DELIMITER);
    strcpy(aluno->nome, ptr);

    ptr = strtok(NULL, DELIMITER);
    aluno->nota = (float) atof(ptr);

    free(line);

    return aluno;
}

/*
 * Escreve todos os alunos de uma hash num arquivo
 * */
void writeAlunosOnFile(FILE *fp, HashAberta *hash) {
    Node *node = hash->elements[0];
    Aluno *aluno;
    do {
        if (node->status == STATUS_OCUPADO) {
            aluno = node->value;
            fprintf(fp, "%d;%s;%s;%.0f\n", node->index, aluno->matricula, aluno->nome, aluno->nota);
        }
        node = node->next;
    } while (node->index != 0);
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Lê o arquivo na URL específicada e preenche as hash de acordo com seu o conteúdo
 * */
HashAberta *readHashAlunoFromFile(HashAberta *hash) {
    FILE *fp = fopen(DIRETORIO_ARQUIVO_ENTRADA, "r");
    int contador = 0;
    int registros;

    printf(MENSSAGE_LENDO_ARQUIVO);

    if (!fp) {
        printf(ERRO_ABRIR_ARQUIVO);
        return hash;
    }

    fscanf(fp, " %d", &registros);
    while (!feof(fp) && contador < registros) {
        Aluno *aluno = readNextAluno(fp);
        hash = insertHash(hash, aluno);
        contador++;
    }

    fclose(fp);
    return hash;
}

/*
 * Cria um arquivo com os registros de uma hash
 * */
void writeHashOnFile(HashAberta *hash) {
    int nomeArquivoSaidaLength = strlen(DIRETORIO_ARQUIVO_SAIDA) + FILE_NAME_MAX_LENGTH + 1;
    char *nomeArquivoSaida = (char *) malloc(nomeArquivoSaidaLength * sizeof(char));
    FILE *fp;

    printf(MENSSAGE_SALVANDO_ARQUIVO);

    sprintf(nomeArquivoSaida, "%ssaida-%s.txt", DIRETORIO_ARQUIVO_SAIDA, hash->label);
    fp = fopen(nomeArquivoSaida, "w");
    if (!fp) {
        printf(ERRO_ABRIR_ARQUIVO);
        return;
    }

    writeAlunosOnFile(fp, hash);

    fclose(fp);
}