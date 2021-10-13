#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluno.h"
#include "HashAberta.h"

#ifndef HASH_FECHADA_CONTROLEARQUIVOALUNO_H
#define HASH_FECHADA_CONTROLEARQUIVOALUNO_H

void readHashAlunoFromFile(HashAberta *hash1, HashAberta *hash2);

void writeHashOnFile(HashAberta *hash);

#endif //HASH_FECHADA_CONTROLEARQUIVOALUNO_H
