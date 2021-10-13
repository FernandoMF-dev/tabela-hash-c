cmake_minimum_required(VERSION 3.20)
project(hash_aberta C)

set(CMAKE_C_STANDARD 99)

add_executable(hash_aberta main.c Aluno.c headers/Aluno.h ControleArquivoAluno.c headers/ControleArquivoAluno.h HashAberta.c headers/HashAberta.h)

target_link_libraries(hash_aberta m)