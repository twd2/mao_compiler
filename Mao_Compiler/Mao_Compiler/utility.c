#include "utility.h"
#include <string.h>

void string_append(char* _destination, const char* _source) {
	int len_destination = strlen(_destination);
	int len_source = strlen(_source);
	for (int i = len_destination; i <= len_destination + len_source; ++i) {
		_destination[i] = _source[i - len_destination];
	}
	return;
}

void string_insert(char* _destination, const char* _source, const unsigned int _position) {
	int len_destination = strlen(_destination);
	int len_source = strlen(_source);
	for (int i = len_destination - 1; i >= _position; --i) {
		_destination[i + len_source] = _destination[i];
	}
	for (int i = _position; i < len_source + _position; ++i) {
		_destination[i] = _source[i - _position];
	}
	_destination[len_destination + len_source] = '\0';
	return;
}
