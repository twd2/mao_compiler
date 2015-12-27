# SXKDZ Mao Interpreter (*SMI*)
## Description
[SXKDZ Mao Interpreter](https://GitHub.com/SXKDZ/mao_interpreter) is a simple [Mao language](https://GitHub.com/SXKDZ/mao_interpreter/blob/master/Requirement/Requirements.pdf) parser. This project is a part of the big homework of C programming language course of the school of software engineering, Tongji University.

SXKDZ Mao Interpreter is written in C completely. The first version of SMC is a simple application of stack.

*Mao Language is designed by Ivan Lin.*

## Features
* Cross-platform
* Implement stack, vector and map in C
* Dynamic memory allocating, for optimized memory using
* Intelligent error catching

## Requirments
* CMake (version >= 3.0)
* gcc (version >= 4.8.0)

## Building
for 32-bits compiling:

you need install ```libc6-dev-i386``` at first

```bash
sudo apt-get install libc6-dev-i386
```

after installing:

```bash
cmake . -DUSE_32BITS=1
make
```

for 64-bits compiling:

``` bash
cmake .
make
```

## Usage
for standard input / output:

``` bash
./smi
```

for file input:

``` bash
./smi source.mao
```

## License
GPL v3
