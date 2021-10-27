#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluno.h"
#include "HashAberta.h"

#ifndef HASH_FECHADA_CONTROLEARQUIVOALUNO_H
#define HASH_FECHADA_CONTROLEARQUIVOALUNO_H

HashAberta *readHashAlunoFromFile(HashAberta *hash);

void writeHashOnFile(HashAberta *hash);

#endif //HASH_FECHADA_CONTROLEARQUIVOALUNO_H
