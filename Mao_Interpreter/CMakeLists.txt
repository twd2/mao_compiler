cmake_minimum_required(VERSION 3.0)
project(Mao_Interpreter)

if(USE_32BITS)
    message(STATUS "using 32bits")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
else()
endif(USE_32BITS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")

set(SOURCE_FILES
	main.c
	memory.h memory.c
	expression.h expression.c
	parser.h parser.c
	stack.h stack.c
	utility.h utility.c
	vector.h vector.c
	map.h map.c)

add_executable(smi ${SOURCE_FILES})
