#pragma once

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "memory.h"
#include <stdbool.h>

typedef enum { HIGH, LOW, SAME, ERROR } _priority;

// Function to check priority between stack_ops's top operator and current operator
extern _priority check_priority(char p1, char p2);

// Function to calculate two variable
extern _variable simple_calculate(char op, _variable a, _variable b);

// Function to get value from a variable to calculate two variables except two integers
extern double get_value(_variable var);

// Function to create a const int variable
extern _variable create_int_variable(int c);

// Function to create a const double variable
extern _variable create_double_variable(double c);

// Function to check whether a character is a operator
extern bool is_operator(char ch);

// Function to check whether a character is a number
extern bool is_number(char ch);

// Function to pharse numbers: add a space after a number or a variable
extern void pharse(char *exp);

// Function to convert infix expression to postfix expression
extern void convert(char *exp);

// Function to calculate a postfix expression
extern double calculate(char *exp);

#endif
