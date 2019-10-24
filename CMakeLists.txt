cmake_minimum_required(VERSION 3.13)
project(vublockchain2)

set(CMAKE_CXX_STANDARD 17)

add_executable(vublockchain2 headers/hash.h headers/main.h main.cpp headers/AustrolopithecusCoin.h headers/Timer.h)