#include "Map.h"
#include <SDL2/SDL_surface.h>

Map::Map()
{
	map = NULL;
	food = NULL;
	oldFood = 99999;
}

Map::~Map()
{
	SDL_FreeSurface(food);
	SDL_FreeSurface(map);
}

void Map::init(const char *fileName, SDL_Surface *blockSheet)
{
	//block = SDL_DisplayFormat(SDL_LoadBMP(blockName));		// Loading the Image of the block

	ifstream mapFile(fileName);								// Parsing the map
	string line;
	int row = 0;

	while(getline(mapFile, line))
	{
		if(line.size() == 0)
			continue;
		if(line[0] == '#')
			continue;

		for(int column = 0; column < 16; column++)
		{
			if(line[column] == '0')
			{
				blocks[row][column] = 0;
			}
			else if(line[column] == '1')
			{
				blocks[row][column] = 1;
			}
			else if(line[column] == '2')
			{
				blocks[row][column] = 2;
			}
			else if(line[column] == '3')
			{
				blocks[row][column] = 3;
			}
			else throw;
		}
		row++;
		if(row == 11)
			break;
	}
	/*for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 16; j++)
			cout << blocks[i][j];
		cout << endl;
	}*/

	SDL_FreeSurface(map);
	SDL_FreeSurface(food);
	map = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);		// Creating the surface of the map
	food = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);		// Creating the surface of the food
	SDL_SetColorKey(food, SDL_TRUE, SDL_MapRGB(food->format, 0, 0, 0));
	SDL_Rect destRect, srcRect;
	srcRect.h = blockSize;
	srcRect.w = blockSize;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = destRect.h = 25;
	for(int i = 0; i < 11; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			if(blocks[i][j] == 1)
			{
				destRect.x = j * blockSize;
				destRect.y = i * blockSize;
				SDL_BlitSurface(blockSheet, &srcRect, map, &destRect);
			}
		}
	}

}

void Map::logic(SDL_Surface *blockSheet, unsigned int newFood)
{
	if(newFood != oldFood)
	{
		SDL_FreeSurface(food);
		food = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);		// Creating the surface of the food
		SDL_SetColorKey(food, SDL_TRUE, SDL_MapRGB(food->format, 0, 0, 0));
		SDL_Rect srcRect, destRect;
		srcRect.x = 2 * blockSize;
		srcRect.y = 0;
		srcRect.w = blockSize;
		srcRect.h = blockSize;
		for(int i = 0; i < 11; i++)
		{
			for(int j = 0; j < 16; j++)
			{
				if(blocks[i][j] == 2)
				{
					destRect.x = j * blockSize;
					destRect.y = i * blockSize;
					SDL_BlitSurface(blockSheet, &srcRect, food, &destRect);
				}
			}
		}
		oldFood = newFood;
	}
}

void Map::show()
{
	SDL_BlitSurface(map, NULL, screen, NULL);
	SDL_BlitSurface(food, NULL, screen, NULL);
}
