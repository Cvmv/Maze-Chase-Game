#include "StdAfx.h"
//#include "Object.h"
#include "Globals.h"
#include "Funcs.h"
#include "KI.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player// : public Object
{
	unsigned int x, y, direction, blocked, blockedDirection, powerUp, eatenFood;
	int xDirVec[5], yDirVec[5];
	unsigned int tempX, tempY;
	bool keyPressed;
	int pressedKey;

public:
	Player();
	Player(unsigned int newX, unsigned int newY);
	~Player();
	void handleEvents();
	void reset(unsigned int newX, unsigned int newY);
	void logic(unsigned int blocks[12][16]);//unsigned int[12][16] blocks);
	unsigned int wallCollision(unsigned int blocks[11][16], int posX, int posY);
	bool enemyCollision(vector<Enemy*> KIVec);
	void show(SDL_Surface *blockSheet);
	unsigned int getEatenFood();

};

#endif