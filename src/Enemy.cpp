#include "Enemy.h"

Enemy::Enemy()
{
	x = y = 0;
	surf = NULL;
}

Enemy::Enemy(SDL_Surface *blockSurf, unsigned int neuX, unsigned int neuY)
{
	surf = blockSurf;
	x = neuX;
	y = neuY;
}

Enemy::~Enemy()
{
	//SDL_FreeSurface(surf);
}

void Enemy::move(int dx, int dy)
{
	x += dx;
	y += dy;
}

void Enemy::show()
{
	SDL_Rect destRect = makeRect(x, y , blockSize, blockSize);
	SDL_Rect srcRect = makeRect(3*blockSize, 0, blockSize, blockSize);
	SDL_BlitSurface(surf, &srcRect, screen, &destRect);
}
