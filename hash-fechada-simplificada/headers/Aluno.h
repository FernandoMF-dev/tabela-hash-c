#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASH_FECHADA_ALUNO_H
#define HASH_FECHADA_ALUNO_H

typedef struct Aluno {
    char *matricula;
    char *nome;
    float nota;
} Aluno;

Aluno newAluno();

Aluno readAluno();

int compareAlunoByKey(Aluno aluno, char *key);

int compareAluno(Aluno aluno1, Aluno aluno2);

void printAluno(Aluno aluno);

#endif //HASH_FECHADA_ALUNO_H
