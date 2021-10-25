CC = gcc
flags = -c -Wall
CFLAGS = -lm
ARQUIVOS = *.o
OBJS = HashAberta.o Aluno.o ControleArquivoAluno.o main.o
EXE = main
MAIN = main.c

all: main.o
	$(CC) $(OBJS) -o $(EXE) -lm
	./main

main.o: main.c HashAberta.o ControleArquivoAluno.o
	$(CC) $(flags) $(MAIN) $(CLFLAGS)

Aluno.o: Aluno.c
	$(CC) $(flags) Aluno.c

ControleArquivoAluno.o: ControleArquivoAluno.c HashAberta.o Aluno.o
	$(CC) $(flags) ControleArquivoAluno.c

HashAberta.o: HashAberta.c Aluno.o
	$(CC) $(flags) HashAberta.c

passos: main.c
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o
	gcc main.o HashAberta.o Aluno.o ControleArquivoAluno.o -o -lm main

run:
	./main

listar:
	ls $(ARQUIVOS)

clean:
	rm -f *.o *.i *.s
	rm -f $(EXE)