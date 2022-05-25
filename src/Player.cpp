#include "Player.h"
//#include <SDL/SDL_events.h>

//erster Konstruktor
Player::Player()
{
	x = y = tempX = tempY = direction = blocked = eatenFood = 0;
	xDirVec[0] = 0;
	xDirVec[1] = 0;
	xDirVec[2] = 1;
	xDirVec[3] = 0;
	xDirVec[4] = -1;

	yDirVec[0] = 0;
	yDirVec[1] = -1;
	yDirVec[2] = 0;
	yDirVec[3] = 1;
	yDirVec[4] = 0;

	pressedKey = 0;
	keyPressed = false;
}

//zweiter Konstruktor
Player::Player(unsigned int newX, unsigned int newY)
{
	x = newX;
	y = newY;
	tempX = tempY = direction = blocked = eatenFood = 0;

	xDirVec[0] = 0;
	xDirVec[1] = 0;
	xDirVec[2] = 1;
	xDirVec[3] = 0;
	xDirVec[4] = -1;

	yDirVec[0] = 0;
	yDirVec[1] = -1;
	yDirVec[2] = 0;
	yDirVec[3] = 1;
	yDirVec[4] = 0;

	pressedKey = 0;
	keyPressed = false;
}

Player::~Player()
{

}

void Player::handleEvents()
{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						direction = 1;
						keyPressed = true;
						pressedKey = SDLK_UP;
						break;
					case SDLK_RIGHT:
						direction = 2;
						keyPressed = true;
						pressedKey = SDLK_RIGHT;
						break;
					case SDLK_DOWN:
						direction = 3;
						keyPressed = true;
						pressedKey = SDLK_DOWN;
						break;
					case SDLK_LEFT:
						direction = 4;
						keyPressed = true;
						pressedKey = SDLK_LEFT;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						if (keyPressed && pressedKey == SDLK_UP) {
							direction = 0;
							keyPressed = false;
						}
						break;
					case SDLK_RIGHT:
						if (keyPressed && pressedKey == SDLK_RIGHT) {
							direction = 0;
							keyPressed = false;		
						}
						break;
					case SDLK_DOWN:
						if (keyPressed && pressedKey == SDLK_DOWN) {
							direction = 0;
							keyPressed = false;			
						}
						break;
					case SDLK_LEFT:
						if (keyPressed && pressedKey == SDLK_LEFT) {
							direction = 0;
							keyPressed = false;			
						}
					break;
				}
		}
}

void Player::logic(unsigned int blocks[11][16])//unsigned int[12][16] blocks)
{
	// Neue Koordinaten auf Kollision pruefen 
	//int posX, posY;
	tempX = x;
	tempY = y;
	
	tempX += xDirVec[direction] * blockSize;
	tempY += yDirVec[direction] * blockSize;

	tempX /= blockSize;
	tempY /= blockSize;

	unsigned int colli = wallCollision(blocks, tempX, tempY);

	if(colli == 1)					//Wand
		direction = blocked = 0;
	
	if(colli == 2)					//Futter
	{
		points += 100;
		blocks[tempY][tempX] = 0;
		eatenFood++;
	}
	
	if(blocked > 0)					//Weg frei
	{
		blocked--;		
		x += xDirVec[blockedDirection] * 5;
		y += yDirVec[blockedDirection] * 5;
	}
	else
	{
		if(direction > 0)
		{
			blockedDirection = direction;
			blocked = 5;
			//direction = 0;
		}
	}

}

unsigned int Player::wallCollision(unsigned int blocks[11][16], int posX, int posY)
{
	if(blocked == 0 && direction != 0)
	{
		if(posX >= 0 && posX < 16 && posY >= 0 && posY < 11)
		{
			return blocks[posY][posX];
		}
		else
			return 1;
	}
	return 0;
}

void Player::show(SDL_Surface *blockSheet)
{
	SDL_Rect destRect = makeRect(x, y, blockSize, blockSize);
	SDL_Rect srcRect = makeRect(blockSize, 0, blockSize, blockSize);
	SDL_BlitSurface(blockSheet, &srcRect, screen, &destRect);
}

bool Player::enemyCollision(vector<Enemy*> KIVec)
{
	SDL_Rect PlayerRect = makeRect(x, y, blockSize, blockSize);
	for(unsigned int i = 0; i < KIVec.size(); i++)
	{
		SDL_Rect enemyRect = makeRect(KIVec[i]->x, KIVec[i]->y, blockSize, blockSize);
		if(collision(&PlayerRect, &enemyRect))
			return true;
	}
	return false;
}

unsigned int Player::getEatenFood()
{
	return eatenFood;
}

void Player::reset(unsigned int newX, unsigned int newY)
{
	x = newX;
	y = newY;
	direction = blocked = 0;
}