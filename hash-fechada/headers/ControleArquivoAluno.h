#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluno.h"
#include "HashFechada.h"

#ifndef HASH_FECHADA_CONTROLEARQUIVOALUNO_H
#define HASH_FECHADA_CONTROLEARQUIVOALUNO_H

void readHashAlunoFromFile(HashFechada *hash1, HashFechada *hash2);

void writeHashOnFile(HashFechada *hash);

#endif //HASH_FECHADA_CONTROLEARQUIVOALUNO_H
