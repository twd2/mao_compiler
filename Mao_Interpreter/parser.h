#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "memory.h"

// Function to parse a statement
void parser(_map *mem, const char *statement);

// Function to catch error
void catch_error(int error_no);

#endif
