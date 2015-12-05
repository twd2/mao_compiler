#include "stack.h"
#include "utility.h"
#include "expression.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int error;

const char OPERATIONS[] = { '+', '-', '*', '/', '#', '(', ')' };
const char NUMBERS[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

_priority check_priority(char p1, char p2) {
	switch (p1) {
	case '+': case '-':
		switch (p2) {
		case '+': case '-': case ')': case '#':
			return HIGH;
		case '*': case '/': case '(': case '$':
			return LOW;
		default:
			return ERROR;
		}
		break;
	case '*': case '/':
		switch (p2) {
		case '+': case '-': case '*': case '/': case ')': case '#':
			return HIGH;
		case '(': case '$':
			return LOW;
		default:
			return ERROR;
		}
		break;
	case '(':
		switch (p2) {
		case '+': case '-': case '*': case '/': case '(': case '$':
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
		case '$': case '(': default:
			return ERROR;
		}
		break;
	case '#':
		switch (p2) {
		case '+': case '-': case '*': case '/': case '(':
			return LOW;
		case '#':
			return SAME;
		case ')': case '$': default:
			return ERROR;
		}
		break;
	case '$':
		return HIGH;
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
			if (b.int_value == 0) {
				result.type = ERRORVALUE;
				result.int_value = DIVIDED_BY_ZERO;
				printf("divided by ZERO\n");
				exit(1);
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
			if (get_value(b) - 0 <= 0.0000001) {
				result.type = ERRORVALUE;
				result.double_value = DIVIDED_BY_ZERO;
				printf("divided by ZERO\n");
				exit(1);
				break;
			}
			break;
		}
	}
	return result;
}

void parse(char *exp) {
	string_append(exp, "#@");
	int i = 0;
	bool number_var_started = false;
	while (exp[i] != '@') {
		if (exp[i] == '-') {
			/* how to judge negative sign:
			 * (1) '(' before this character - negative sign;
			 * (2) ')' or numbers before this character - minus sign;
			 * (3) other optional character before this character - negative sign;
			 * (4) this character is the first - negative sign.
			 *
			 * special process with negative sign:
			 *  - change the minus sign to another new sign '$';
			 *  - change the priority of the new sign to the highest;
			 *  - when calculate the new sign:
			 *     * push back the opt '$';
			 *     * when come up with '$', get the top one var of ovs_stack.
			 */
			if (i == 0 || exp[i - 1] == '(' ||
				exp[i - 1] == '+' || exp[i - 1] == '-' ||
				exp[i - 1] == '*' || exp[i - 1] == '/') {
				string_replace(exp, '$', i);
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

	_stack *stack_ops = stack_new(1);
	_stack *stack_ovs = stack_new(1);
	stack_push_constant(stack_ops, (int)'#');

	int length = strlen(exp);
	char exp_tmp_str[2005] = {'\0'};
	bool number_var_started = false;
	
	for (int i = 0; i < length; ++i) {
		if (exp[i] == '@') {
			break;
		}
		if (is_operator(exp[i]) || exp[i] == '$') {
			if (check_priority(*(char *)(*stack_top(stack_ops)), exp[i]) == ERROR) {
				error = LOGIC_ERROR;
				break;
			}
			while (check_priority(*(char *)(*stack_top(stack_ops)), exp[i]) == HIGH) {
				char ops_str[2];
				ops_str[0] = *(char *)(*stack_top(stack_ops));
				ops_str[1] = '\0';
				stack_pop(stack_ops);

				size_t ovs_str1_len = strlen((char *)(*stack_top(stack_ovs)));
				char *ovs_str1 = (char *)malloc((ovs_str1_len + 1) * sizeof(char));
				strcpy(ovs_str1, (char *)(*stack_top(stack_ovs)));
				stack_pop(stack_ovs);

				size_t ovs_str2_len = strlen((char *)(*stack_top(stack_ovs)));
				char *ovs_str2 = (char *)malloc((ovs_str2_len + ovs_str1_len + 3) * sizeof(char));
				strcpy(ovs_str2, (char *)(*stack_top(stack_ovs)));
				stack_pop(stack_ovs);

				strcat(ovs_str2, ovs_str1);
				strcat(ovs_str2, ops_str);
				stack_push_string(stack_ovs, ovs_str2, strlen(ovs_str2));

				free(ovs_str1);
				free(ovs_str2);
			}
			if (check_priority(*(char *)(*stack_top(stack_ops)), exp[i]) == LOW) {
				stack_push_constant(stack_ops, (int)exp[i]);
			}
			else {
				stack_pop(stack_ops);
			}
		}
		else if (is_number(exp[i]) || isalpha(exp[i]) || exp[i] == '.') {
			char exp_str[2];
			exp_str[0] = exp[i];
			exp_str[1] = '\0';

			if (number_var_started) {
				strcat(exp_tmp_str, exp_str);
			}
			else {
				exp_tmp_str[0] = exp[i];
				exp_tmp_str[1] = '\0';
				number_var_started = true;
			}
		}
		else if (exp[i] == ' ' && number_var_started) {
			strcat(exp_tmp_str, " ");
			stack_push_string(stack_ovs, exp_tmp_str, strlen(exp_tmp_str));
			exp_tmp_str[0] = '\0';
			number_var_started = false;
		}
	}
	strcpy(exp, (char *)(*stack_top(stack_ovs)));

	stack_free(stack_ops);
	stack_free(stack_ovs);
	return;
}

_variable calculate(_memory *mem, char *exp) {

	int length = strlen(exp);
	bool number_started = false;
	bool var_started = false;
	bool is_double = false;
	char temp_string[2005];
	int iterator = 0;

	_stack *stack_ovs = stack_new(1);

	for (int i = 0; i < length; ++i) {
		if (is_operator(exp[i])) {
			_variable b = *(_variable *)(*(stack_top(stack_ovs)));
			stack_pop(stack_ovs);
			_variable a = *(_variable *)(*(stack_top(stack_ovs)));
			stack_pop(stack_ovs);
			_variable res = simple_calculate(exp[i], b, a);
			stack_push(stack_ovs, &res, sizeof(res));
			if (((_variable *)(*(stack_top(stack_ovs))))->type == ERRORVALUE) {
				return *(_variable *)(*(stack_top(stack_ovs)));
			}
		}
		else if (exp[i] == '$') {
			_variable var = *(_variable *)(*(stack_top(stack_ovs)));
			_variable zero;
			zero.type = var.type;
			zero.double_value = 0;
			zero.int_value = 0;
			_variable res = simple_calculate('-', zero, var);
			stack_push(stack_ovs, &res, sizeof(res));
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
				_variable var = *get_variable_by_name(mem, temp_string);
				if (var.type == DOUBLE) {
					is_double = true;
				}
				stack_push(stack_ovs, &var, sizeof(var));
				var_started = false;
			}
			else if (number_started) {
				_variable var;
				char *end;
				if (strchr(temp_string, '.')) {
					double value = strtod(temp_string, &end);
					var = create_double_variable(value);
					is_double = true;
				}
				else {
					int value = strtol(temp_string, &end, 10);
					var = create_int_variable(value);
				}
				stack_push(stack_ovs, &var, sizeof(var));
				number_started = false;
			}
		}
	}
	_variable result;
	result.type = is_double ? DOUBLE : INT;
	switch (result.type)
	{
	case INT:
		result.int_value = get_value(*(_variable *)(*(stack_top(stack_ovs))));
		break;
	case DOUBLE:
		result.double_value = get_value(*(_variable *)(*(stack_top(stack_ovs))));
		break;
	}
	stack_free(stack_ovs);
	return result;
}
