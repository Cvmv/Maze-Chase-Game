#include "StdAfx.h"
#include "Globals.h"
#include "Funcs.h"
//#include "Object.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy// : public Object
{
	SDL_Surface *surf;
	unsigned int x, y;
public:
	Enemy();
	Enemy(SDL_Surface *blockSurf, unsigned int neuX, unsigned int neuY);
	~Enemy();
	void move(int dx, int dy);
	//void moveToNextSquare(unsigned int direction);
	void show();
	friend class KI;
	friend class Player;
};

#endif