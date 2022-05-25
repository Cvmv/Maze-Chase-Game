#include "Game.h"

Game::Game(const char *mapName, const char *blockName)
{
	//cout << "Game Constructor" << endl;
	blocks = SDL_LoadBMP(blockName);
	if(blocks == NULL) {
		cout << "Blocks could not be loaded!: " << SDL_GetError() << endl;
	}
	SDL_SetColorKey(blocks, SDL_TRUE, SDL_MapRGB(blocks->format, 0, 0, 0));

	lives = 3;
	totalFood = 0;
	name = mapName;
	map = new Map();

	map->init(name, blocks);
	player1 = new Player(0, 0);
	ki = new KI(blocks, map->blocks);
	ui = new Ui();
	for(unsigned int row = 0; row < 11; row++)
	{
		for(unsigned int column = 0; column < 16; column++)
		{
			if(map->blocks[row][column] == 2)
				totalFood++;
		}
	}
}

Game::~Game()
{
	SDL_FreeSurface(blocks);
	delete ui;
	delete ki;
	delete player1;
	delete map;
}

void Game::handleEvents()
{
	//cout << "Game Handle Events" << endl;
	while(SDL_PollEvent(&event))
	{
		player1->handleEvents();
		switch(event.type)
		{
		case SDL_QUIT:
			nextState = StateExit;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				nextState = StateNewHighscore;
				break;
			}
		}
	}
}

void Game::logic()
{
	//cout << "Game Logic" << endl;
	map->logic(blocks, player1->getEatenFood());

	player1->logic(map->blocks);

	ki->logic();

	if(player1->getEatenFood() >= totalFood)
	{
		map->init(name, blocks);
		delete player1;
		player1 = new Player(0, 0);
	}
	if(player1->enemyCollision(ki->enemy))
	{
		if(lives > 0)
		{
			lives -= 1;
			//map->init(name, blocks);
			//delete player1;
			//player1 = new Player(0, 0);
			player1->reset(0,0);
		}
		else nextState = StateNewHighscore;
	}

	ui->logic();
}

void Game::render()
{
	//cout << "Game Render" << endl;
	map->show();

	player1->show(blocks);

	ki->show();

	ui->show();
}
