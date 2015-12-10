cmake_minimum_required(VERSION 3.0)
project(Mao_Interpreter)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")

set(SOURCE_FILES
        main.c
        memory.h memory.c
        expression.h expression.c
        parser.h parser.c
        stack.h stack.c
        utility.h utility.c
        vector.h vector.c)

add_executable(Mao_Interpreter ${SOURCE_FILES})
