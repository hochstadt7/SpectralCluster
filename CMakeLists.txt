cmake_minimum_required(VERSION 3.17)
project(SpecturalCluster C)

set(CMAKE_C_STANDARD 90)

add_executable(SpecturalCluster GramShmidt.c Qr.c ShmidtAux.c ShmidtAux.h Qr.h GramShmidt.h EigenValsCPython.c)