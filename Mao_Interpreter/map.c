#include "map.h"

_map *map_new_node(void) {
	_map *node = (_map *)malloc(sizeof(_map));
	node->value = NULL;
	for (int i = 0; i < 256; ++i) {
		node->sub_nodes[i] = NULL;
	}
	return node;
}

void map_new_subnode(_map *node, char key) {
	node->sub_nodes[key] = map_new_node();
	return;
}

void map_add(_map *node, const char *str, void *value) {
	if (*str == '\0') {
		node->value = value;
		return;
	}
	if (!node->sub_nodes[*str]) {
		map_new_subnode(node, *str);
	}
	map_add(node->sub_nodes[*str], str + 1, value);
	return;
}

void **map_get(_map *node, const char *str) {
	if (*str == '\0') {
		return &(node->value);
	}
	if (node->sub_nodes[*str]) {
		return map_get(node->sub_nodes[*str], str + 1);
	}
	else {
		return NULL;
	}
}

void map_free(_map *node) {
	if (!node) {
		return;
	}
	node->value = NULL;
	for (int i = 0; i < 256; ++i) {
		if (node->sub_nodes[i]) {
			map_free(node->sub_nodes[i]);
		}
		node->sub_nodes[i] = NULL;
	}
	free(node);
	node = NULL;
	return;
}

void map_deepfree(_map *node) {
	if (!node) {
		return;
	}
	if (node->value) {
		free(node->value);
		node->value = NULL;
	}
	for (int i = 0; i < 256; ++i) {
		if (node->sub_nodes[i]) {
			map_deepfree(node->sub_nodes[i]);
		}
		node->sub_nodes[i] = NULL;
	}
	free(node);
	node = NULL;
	return;
}
