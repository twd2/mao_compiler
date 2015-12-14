#pragma once

#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct _map {
	void *value;
	struct _map *sub_nodes[256];
} _map;

// Function to add a new node to the map or create a new map
_map *map_new_node(void);

// Function to add a new subnode to the map
void map_new_subnode(_map *node, char key);

// Function to add a string with it's paired value to the map
void map_add(_map *node, const char *str, void *value);

// Function to get a value in corresponding with the string
void **map_get(_map *node, const char *str);

// Function to free a map preserving the value
void map_free(_map *node);

// Function to free a map completely
void map_deepfree(_map *node);

#endif
