#include "StdAfx.h"
#include "Globals.h"

#ifndef MAP_H
#define MAP_H

class Map
{
	SDL_Surface *map;
	SDL_Surface *food;
	unsigned int oldFood;
public:
	unsigned int blocks[11][16];
	Map();
	~Map();
	void init(const char *fileName, SDL_Surface *blockSheet);
	void logic(SDL_Surface *blockSheet, unsigned int newFood);
	void show();
	//unsigned int[11][16] getBlocks() {return blocks;};
};

#endif