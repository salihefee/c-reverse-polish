cmake_minimum_required(VERSION 3.30)
project(rpn C)

set(CMAKE_C_STANDARD 23)

add_executable(rpn src/main.c src/stack.c src/operations.c)
