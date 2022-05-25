#include "KI.h"

KI::KI()
{
	surf = 0;
	tempX = tempY = timer = playerX = playerY = 0;

	blockedDirVec[0] = 0;
	blockedDirVec[1] = 3;
	blockedDirVec[2] = 4;
	blockedDirVec[3] = 1;
	blockedDirVec[4] = 2;

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

	//Rand initialisieren
	time_t sek;
	time(&sek);
	srand((unsigned)sek);
}

KI::KI(SDL_Surface *blockSurf, const unsigned int blockMap[11][16])
{
	surf = blockSurf;
	tempX = tempY = timer = playerX = playerY = 0;

	blockedDirVec[0] = 0;
	blockedDirVec[1] = 3;
	blockedDirVec[2] = 4;
	blockedDirVec[3] = 1;
	blockedDirVec[4] = 2;

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

	//Rand initialisieren
	time_t sek;
	time(&sek);
	srand((unsigned)sek);

	for(int i = 0; i < 11; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			blocks[i][j] = blockMap[i][j];

			if(blockMap[i][j] == 3)
			{
				enemy.push_back(new Enemy(surf, j * blockSize, i * blockSize));
				enemyDir.push_back(0);
			}
		}
	}
}
KI::~KI()
{

}

void KI::logic()
{
	if(timer == 0)
	{
		timer = 5;
		for(unsigned int i = 0; i<enemyDir.size(); i++)
			enemyDir[i] = calcNextMove(enemy[i], enemyDir[i]);
	}
	else
	{
		timer--;
		for(unsigned int j = 0; j<enemy.size(); j++)
			enemy[j]->move(5*xDirVec[enemyDir[j]], 5*yDirVec[enemyDir[j]]);
	}

}

void KI::show()
{
	for(unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->show();
	}
}

//Berechnet einen zufälligen Zug
unsigned int KI::calcNextMove(Enemy *enemy, unsigned int oldDirection)
{
	unsigned int nextDirection = 0, blockedDirection = 0;
	bool validDirectionFound = false;

	//Überprüfen, ob Gegner in seiner Richtung weiter gehen kann
	//und dann umdrehen blockieren
	tempX = enemy->x/blockSize + xDirVec[oldDirection];
	tempY = enemy->y/blockSize + yDirVec[oldDirection];



	if(tempY < 11 && tempX < 16 && tempY >= 0 && tempX >= 0) // neue Position auf Spielfeld
    {
        if(blocks[tempY][tempX] != 1) // und keine Wand
        {
            blockedDirection = blockedDirVec[oldDirection];
        }
    }
	/*if(blocks[tempY][tempX] != 1		//neue Position keine Wand
		&& tempY < 11 && tempX < 16)	//und auf dem Spielfeld
	{
	    cout << "blockdirection" << endl;
		blockedDirection = blockedDirVec[oldDirection];
	}*/

	while(!validDirectionFound)
	{
		nextDirection = (rand()%4)+1;		//Kein Stillstand zulassen
		//nextDirection = rand()%5;			//Mit Stillstand

		//Neue Position auf GültigKeit Überprüfen
		tempX = enemy->x/blockSize + xDirVec[nextDirection];
		tempY = enemy->y/blockSize + yDirVec[nextDirection];

		if(tempY < 11 && tempX < 16 && tempY >= 0 && tempX >= 0) // neue Position auf Spielfeld
        {
            if(blocks[tempY][tempX] != 1				//neue Position keine Wand
                && nextDirection != blockedDirection)
                validDirectionFound = true;
        }
	}

	return nextDirection;



}
