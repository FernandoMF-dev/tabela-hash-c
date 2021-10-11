#include "headers/Aluno.h"

#define MATRICULA_MAX_LENGTH 15
#define NOME_MAX_LENGTH 255

/*
Cria e retorna uma nova instância vazia de Aluno
*/
Aluno *newAluno() {
    Aluno *aluno = (Aluno *) malloc(sizeof(Aluno));

    aluno->matricula = (char *) malloc((MATRICULA_MAX_LENGTH + 1) * sizeof(char));
    aluno->nome = (char *) malloc((NOME_MAX_LENGTH + 1) * sizeof(char));
    aluno->nota = 0;

    return aluno;
}

/*
Lê e retorna um novo aluno do terminal
*/
Aluno *readAluno() {
    Aluno *aluno = newAluno();

    printf("\nMatricula(%d): ", MATRICULA_MAX_LENGTH);
    scanf(" %s", aluno->matricula);
    getchar();

    printf("Nome(%d): ", NOME_MAX_LENGTH);
    scanf(" %[^\n]s", aluno->nome);
    getchar();

    printf("Nota: ");
    scanf(" %f", &aluno->nota);

    return aluno;
}

/*
Compara se uma chave (key) corresponde a matrícula de um aluno.

Se sim, retorna 0.
Se a chave for maior, retorna um inteiro maior que 0.
Se a chave for menor, retorna um inteiro menor que 0.
*/
int compareAlunoByKey(Aluno *aluno, char *key) {
    return strcmp(aluno->matricula, key);
}

int compareAluno(Aluno *aluno1, Aluno *aluno2) {
    int result = strcmp(aluno1->matricula, aluno2->matricula);

    if (result == 0) {
        result = strcmp(aluno1->nome, aluno2->nome);
        if (result == 0) {
            result = (int) (aluno1->nota - aluno2->nota);
        }
    }

    return result;
}

/*
Imprime os valores de um Aluno
*/
void printAluno(Aluno *aluno) {
    printf("{ 'Matricula': '%s', 'Nome': '%s', 'Nota': %.2f }", aluno->matricula, aluno->nome, aluno->nota);
}