#include "utility.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>

void string_append(char* _des, const char* _src) {
	int len_destination = strlen(_des);
	int len_source = strlen(_src);
	for (int i = len_destination; i <= len_destination + len_source; ++i) {
		_des[i] = _src[i - len_destination];
	}
	return;
}

void string_insert(char* _des, const char* _src, const unsigned int _pos) {
	int len_destination = strlen(_des);
	int len_source = strlen(_src);
	for (int i = len_destination - 1; i >= _pos; --i) {
		_des[i + len_source] = _des[i];
	}
	for (int i = _pos; i < len_source + _pos; ++i) {
		_des[i] = _src[i - _pos];
	}
	_des[len_destination + len_source] = '\0';
	return;
}

void string_sub(char *_des, const char *_src, const unsigned int _pos, const unsigned int _len) {
	char *p_source = _src + _pos;
	for (int i = 0; i < _len; ++i) {
		_des[i] = *(p_source++);
	}
	_des[_len] = '\0';
	return;
}

int string_split(_vector *vec, const char *src, const char delim) {
	int len = strlen(src);
	int last_pos = 0, count = 0;
	for (int i = 0; i <= len; ++i) {
		if (src[i] == delim || src[i] == '\0') {
			char *des = (char *)malloc((i - last_pos + 1) * sizeof(char));
			string_sub(des, src, last_pos, i - last_pos);
			vector_add(vec, (void *)des);
			last_pos = i + 1;
			++count;
		}
	}
	return count;
}
