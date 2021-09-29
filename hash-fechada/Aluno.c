#include "headers/Aluno.h"

#define MATRICULA_MAX_LENGTH 16
#define NOME_MAX_LENGTH 255

Aluno newAluno() {
    Aluno aluno;

    aluno.matricula = (char *) malloc((MATRICULA_MAX_LENGTH + 1) * sizeof(char));
    aluno.nome = (char *) malloc((NOME_MAX_LENGTH + 1) * sizeof(char));
    aluno.nota = 0;

    return aluno;
}

Aluno readAluno() {
    Aluno aluno = newAluno();

    printf("\nMatricula(%d): ", MATRICULA_MAX_LENGTH);
    scanf(" %s", aluno.matricula);
    getchar();

    printf("\nNome(%d): ", NOME_MAX_LENGTH);
    scanf(" %s", aluno.nome);
    getchar();

    printf("\nNota: ");
    scanf(" %f", &aluno.nota);

    return aluno;
}

int compareAlunoByKey(Aluno aluno, char *key) {
    return strcmp(aluno.matricula, key);
}

void printAluno(Aluno aluno) {
    printf("{ 'Matricula': '%s', 'Nome': '%s', 'Nota': %.2f }", aluno.matricula, aluno.nome, aluno.nota);
}