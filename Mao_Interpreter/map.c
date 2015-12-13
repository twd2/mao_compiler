#include "map.h"

_map *map_node_new()
{
	_map *node = (_map *)malloc(sizeof(_map));
	node->value = NULL;
	for (int i = 0; i < 256; ++i)
	{
		node->subNodes[i] = NULL;
	}
	return node;
}

_map *map_new()
{
	return map_node_new();
}

void map_newSubNode(_map* node, char key)
{
	if (node->subNodes[key]) return;
	node->subNodes[key] = map_node_new();
}

void map_add(_map* node, const char *str, void *value)
{
	if (*str == '\0')
	{
		node->value = value;
		return;
	}
	if (!node->subNodes[*str])
	{
		map_newSubNode(node, *str);
	}
	map_add(node->subNodes[*str], str + 1, value);
}

void** map_get(_map* node, const char *str)
{
	if (*str == '\0')
	{
		return &(node->value);
	}
	if (node->subNodes[*str])
		return map_get(node->subNodes[*str], str + 1);
	else
		return NULL;
}

void map_free(_map *node)
{
	if (!node) return;
	node->value = NULL;
	for (int i = 0; i < 256; ++i)
	{
		if (node->subNodes[i])
			map_free(node->subNodes[i]);
		node->subNodes[i] = NULL;
	}
	free(node);
	node = NULL;
}

void map_deepfree(_map *node)
{
	if (!node) return;
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	for (int i = 0; i < 256; ++i)
	{
		if (node->subNodes[i])
			map_deepfree(node->subNodes[i]);
		node->subNodes[i] = NULL;
	}
	free(node);
	node = NULL;
}
