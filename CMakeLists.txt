cmake_minimum_required(VERSION 4.0)
project(chess C)

set(CMAKE_C_STANDARD 90)

add_executable(chess main.c
        movevalidity.c
        chess.h
        globalvalidity.c
)
