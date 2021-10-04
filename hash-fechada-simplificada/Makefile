CC = gcc
flags = -c -Wall
CFLAGS = -lm
ARQUIVOS = *.o
OBJS = Node.o HashFechada.o Aluno.o Lista.o ControleArquivoAluno.o main.o
EXE = main
MAIN = main.c

all: main.o
	$(CC) $(OBJS) -o $(EXE) -lm
	./main

main.o: main.c HashFechada.o ControleArquivoAluno.o
	$(CC) $(flags) $(MAIN) $(CLFLAGS)

Node.o: Node.c Aluno.o
	$(CC) $(flags) Node.c

Aluno.o: Aluno.c
	$(CC) $(flags) Aluno.c

Lista.o: Lista.c Aluno.o Node.o
	$(CC) $(flags) Lista.c

ControleArquivoAluno.o: ControleArquivoAluno.c HashFechada.o Aluno.o
	$(CC) $(flags) ControleArquivoAluno.c

HashFechada.o: HashFechada.c Lista.o Aluno.o
	$(CC) $(flags) HashFechada.c

passos: main.c
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o
	gcc main.o Node.o HashFechada.o Aluno.o Lista.o ControleArquivoAluno.o -o -lm main

run:
	./main

listar:
	ls $(ARQUIVOS)

clean:
	rm -f *.o *.i *.s
	rm -f $(EXE)