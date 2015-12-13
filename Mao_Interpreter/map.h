#pragma once

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct _map;
typedef struct _map _map;
struct _map
{
	void *value;
	_map *subNodes[256];
};

_map *map_node_new();
_map *map_new();
void map_newSubNode(_map* node, char key);
void map_add(_map* node, const char *str, void *value);
void** map_get(_map* node, const char *str);
void map_free(_map *node);
void map_deepfree(_map *node);

#endif //MAP_H
