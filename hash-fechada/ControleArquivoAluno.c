#include "headers/ControleArquivoAluno.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERRO_ABRIR_ARQUIVO "\n\tERRO: Erro na abertura do arquivo!\n"

#define MENSSAGE_LENDO_ARQUIVO "\n\tAVISO: Lendo arquivo, por favor aguarde...\n"
#define DIRETORIO_ARQUIVO_ENTRADA "../entrada/entrada.txt"
#define DIRETORIO_ARQUIVO_SAIDA "../saida/"
#define LINE_MAX_LENGTH 511
#define DELIMITER ";"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

Aluno readNextAluno(FILE *fp);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

Aluno readNextAluno(FILE *fp) {
    Aluno aluno = newAluno();
    char *line = (char *) malloc((LINE_MAX_LENGTH + 1) * sizeof(char));
    char *ptr;

    fscanf(fp, " %[^\n]%*c", line);
    ptr = strtok(line, DELIMITER);
    strcpy(aluno.matricula, ptr);

    ptr = strtok(NULL, DELIMITER);
    strcpy(aluno.nome, ptr);

    ptr = strtok(NULL, DELIMITER);
    aluno.nota = (float) atof(ptr);

    return aluno;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

void readHashAlunoFromFile1(HashFechada *hash) {
    FILE *fp = fopen(DIRETORIO_ARQUIVO_ENTRADA, "r");
    int qntd;

    if (!fp) {
        printf(ERRO_ABRIR_ARQUIVO);
        return;
    }

    printf(MENSSAGE_LENDO_ARQUIVO);
    fscanf(fp, "%d", &qntd);
    while (!feof(fp)) {
        insertHash(hash, readNextAluno(fp));
    }

    fclose(fp);
}

void readHashAlunoFromFile2(HashFechada *hash1, HashFechada *hash2) {
    FILE *fp = fopen(DIRETORIO_ARQUIVO_ENTRADA, "r");
    int qntd;

    if (!fp) {
        printf(ERRO_ABRIR_ARQUIVO);
        return;
    }

    printf(MENSSAGE_LENDO_ARQUIVO);
    fscanf(fp, "%d", &qntd);
    while (!feof(fp)) {
        Aluno aluno = readNextAluno(fp);
        insertHash(hash1, aluno);
        insertHash(hash2, aluno);
    }

    fclose(fp);
}