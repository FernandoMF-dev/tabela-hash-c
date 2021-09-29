cmake_minimum_required(VERSION 3.20)
project(hash_fechada C)

set(CMAKE_C_STANDARD 99)

add_executable(hash_fechada main.c Lista.c headers/Lista.h Node.c headers/Node.h)
