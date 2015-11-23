#include "expression.h"
#include "utility.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int error;

const char OPERATIONS[] = { '+', '-', '*', '/', '#', '(', ')' };
const char NUMBERS[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

// TODO: no longer global variables
char stack_ovs[2005][2005];
char stack_ops[2005];
_variable stack_cal_ovs[2005];
int stack_ovs_top = -1;
int stack_ops_top = -1;
int stack_cal_ovs_top = -1;

_priority check_priority(char p1, char p2) {
	switch (p1) {
	case '+': case '-':
		switch (p2) {
		case '+': case '-': case ')': case '#':
			return HIGH;
		case '*': case '/': case '(':
			return LOW;
		default:
			return ERROR;
		}
		break;
	case '*': case '/':
		switch (p2) {
		case '+': case '-': case '*': case '/': case ')': case '#':
			return HIGH;
		case '(':
			return LOW;
		default:
			return ERROR;
		}
		break;
	case '(':
		switch (p2) {
		case '+': case '-': case '*': case '/': case '(':
			return LOW;
		case ')':
			return SAME;
		case '#': default:
			return ERROR;
		}
		break;
	case ')':
		switch (p2) {
		case '+': case '-': case '*': case '/': case ')': case '#':
			return HIGH;
		case '(': default:
			return ERROR;
		}
		break;
	case '#':
		switch (p2) {
		case '+': case '-': case '*': case '/': case '(':
			return LOW;
		case '#':
			return SAME;
		case ')': default:
			return ERROR;
		}
		break;
	}
	return ERROR;
}

_variable create_int_variable(int c) {
	_variable var;
	var.int_value = c;
	var.type = INT;
	return var;
}

_variable create_double_variable(double c) {
	_variable var;
	var.double_value = c;
	var.type = DOUBLE;
	return var;
}

double get_value(_variable var) {
	double result;
	if (var.type == INT) {
		result = (double)var.int_value;
	}
	else {
		result = var.double_value;
	}
	return result;
}

bool is_operator(char ch) {
	for (int i = 0; i < sizeof(OPERATIONS) / sizeof(*OPERATIONS); ++i) {
		if (OPERATIONS[i] == ch) {
			return true;
		}
	}
	return false;
}

bool is_number(char ch) {
	for (int i = 0; i < sizeof(NUMBERS) / sizeof(*NUMBERS); ++i) {
		if (NUMBERS[i] == ch) {
			return true;
		}
	}
	return false;
}

_variable simple_calculate(char op, _variable a, _variable b) {
	_variable result;
	if (a.type == INT && b.type == INT) {
		result.type = INT;
		switch (op)
		{
		case '+':
			result.int_value = a.int_value + b.int_value;
			break;
		case '-':
			result.int_value = a.int_value - b.int_value;
			break;
		case '*':
			result.int_value = a.int_value * b.int_value;
			break;
		case '/':
			if (b.int_value == 0)
			{
				result.type = ERRORVALUE;
				result.int_value = DIVIDED_BY_ZERO;
				break;
			}
			result.int_value = a.int_value / b.int_value;
			break;
		}
	}
	else {
		result.type = DOUBLE;
		switch (op)
		{
		case '+':
			result.double_value = get_value(a) + get_value(b);
			break;
		case '-':
			result.double_value = get_value(a) - get_value(b);
			break;
		case '*':
			result.double_value = get_value(a) * get_value(b);
			break;
		case '/':
			result.double_value = get_value(a) / get_value(b);
			break;
		}
	}
	return result;
}

void pharse(char *exp) {
	string_append(exp, "#@");
	int i = 0;
	bool number_var_started = false;
	while (exp[i] != '@') {
		if (exp[i] == '-') {
			if (i == 0 || is_operator(exp[i - 1])) {
				string_insert(exp, "0", i);
			}
		}
		if (is_number(exp[i]) || isalpha(exp[i]) || exp[i] == '.') {
			if (!number_var_started) {
				number_var_started = true;
			}
		}
		else if (number_var_started) {
			string_insert(exp, " ", i);
			number_var_started = false;
		}
		i++;
	}
	return;
}

void convert(char *exp) {

	stack_ops[++stack_ops_top] = '#';

	int length = strlen(exp);
	bool number_var_started = false;
	
	for (int i = 0; i < length; ++i) {
		if (exp[i] == '@') {
			break;
		}
		if (is_operator(exp[i])) {
			if (check_priority(stack_ops[stack_ops_top], exp[i]) == ERROR) {
				error = LOGIC_ERROR;
				break;
			}
			while (check_priority(stack_ops[stack_ops_top], exp[i]) == HIGH) {
				char ops_str[2];
				ops_str[0] = stack_ops[stack_ops_top--];
				ops_str[1] = '\0';

				strcat(stack_ovs[stack_ovs_top - 1], stack_ovs[stack_ovs_top]);
				strcat(stack_ovs[stack_ovs_top - 1], ops_str);
				stack_ovs_top--;
			}
			if (check_priority(stack_ops[stack_ops_top], exp[i]) == LOW) {
				stack_ops[++stack_ops_top] = exp[i];
			}
			else {
				stack_ops_top--;
			}
		}
		else if (is_number(exp[i]) || isalpha(exp[i]) || exp[i] == '.') {
			char exp_str[2];
			exp_str[0] = exp[i];
			exp_str[1] = '\0';

			if (number_var_started) {
				strcat(stack_ovs[stack_ovs_top], exp_str);
			}
			else {
				strcpy(stack_ovs[++stack_ovs_top], exp_str);
				number_var_started = true;
			}
		}
		else if (exp[i] == ' ') {
			strcat(stack_ovs[stack_ovs_top], " ");
			number_var_started = false;
		}
	}
	strcpy(exp, stack_ovs[stack_ovs_top]);
	return;
}

_variable calculate(_memory *mem, char *exp) {

	int length = strlen(exp);
	bool number_started = false;
	bool var_started = false;
	char temp_string[2005];
	int iterator = 0;

	for (int i = 0; i < length; ++i) {
		if (is_operator(exp[i])) {
			_variable a = stack_cal_ovs[stack_cal_ovs_top - 1];
			_variable b = stack_cal_ovs[stack_cal_ovs_top];
			stack_cal_ovs_top--;
			stack_cal_ovs[stack_cal_ovs_top] = simple_calculate(exp[i], a, b);
			if (stack_cal_ovs[stack_cal_ovs_top].type == ERRORVALUE) {
				return stack_cal_ovs[stack_cal_ovs_top];
			}
		}
		else if (isalpha(exp[i])) {
			// pharse variable's name
			if (var_started) {
				temp_string[iterator++] = exp[i];
			}
			else if (!var_started && !number_started) {
				// if it's the begin of a variable's name
				var_started = true;
				temp_string[iterator++] = exp[i];
			}
		}
		else if (is_number(exp[i]) || exp[i] == '.') {
			// there're two occasions: number's begin or variable's name
			if (number_started || var_started) {
				temp_string[iterator++] = exp[i];
			}
			else if (!var_started && !number_started) {
				number_started = true;
				temp_string[iterator++] = exp[i];
			}
		}
		else if (exp[i] == ' ') {
			temp_string[iterator++] = '\0';
			iterator = 0;
			if (var_started) {
				_variable var = get_variable_by_name(mem, temp_string);
				stack_cal_ovs[++stack_cal_ovs_top] = var;
				var_started = false;
			}
			else if (number_started) {
				_variable var;
				char *end;
				if (strchr(temp_string, '.')) {
					double value = strtod(temp_string, &end, 10);
					var = create_double_variable(value);
				}
				else {
					int value = strtol(temp_string, &end, 10);
					var = create_int_variable(value);
				}
				stack_cal_ovs[++stack_cal_ovs_top] = var;
				number_started = false;
			}
		}
	}
	_variable result;
	result.type = DOUBLE;
	result.double_value = get_value(stack_cal_ovs[stack_cal_ovs_top]);
	return result;
}
