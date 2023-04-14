cmake_minimum_required(VERSION 3.25)
project(yukon_solitaire C)

set(CMAKE_C_STANDARD 11)

include_directories(code)

add_executable(yukon_solitaire
        code/Card.c
        code/Card.h
        code/DoublyLinkedList.c
        code/DoublyLinkedList.h
        code/Foundation.c
        code/Foundation.h
        code/Game.c
        code/View.c
        code/View.h code/Cli.c code/Cli.h)
