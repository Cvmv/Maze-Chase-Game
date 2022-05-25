#include "StdAfx.h"
#include "Enemy.h"

#ifndef KI_H
#define KI_H

class KI
{
	vector<Enemy*> enemy;
	vector<unsigned int> enemyDir;
	SDL_Surface *surf;
	int xDirVec[5], yDirVec[5], blockedDirVec[5];
	unsigned int tempX, tempY, timer, playerX, playerY;
	unsigned int blocks[11][16];


public:
	KI();
	KI(SDL_Surface *blockSurf, const unsigned int blockMap[11][16]);
	~KI();
	void logic();
	void show();
	unsigned int calcNextMove(Enemy *enemy, unsigned int oldDirection);
	friend class Player;
	friend class Game;
};

#endif