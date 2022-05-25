#include "StdAfx.h"
#include "BaseClass.h"
#include "Menu.h"
#include "Highscore.h"
#include "NewHighscore.h"
#include "Game.h"
#include <SDL2/SDL_surface.h>

#ifdef _WIN32
#undef main
#endif

void changeState();

int main()
{
	if(!init())
		return 1;
	if(screen == NULL)
		cout << "NULL";
	if(!loadFiles())
		return 1;
	currentState = new Menu;

	while(stateID != StateExit)
	{
		//cout << "run0" << endl;
		int start = SDL_GetTicks();
		
		currentState->handleEvents();
		currentState->logic();
		
		changeState();
		
		currentState->render();

		if (SDL_UpdateWindowSurface(gWindow) < 0) {
			printf("Windowsurface could not be updated! SDL Error: %s\n", SDL_GetError());
			
		}
	
		if (1000/FPS > SDL_GetTicks() - start)
			SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
	}
	cleanUp();
}

void changeState()
{
	if(nextState != StateNull)
	{
		if(nextState != StateExit)
		{
			delete currentState;
			currentState = NULL;
		}

		switch(nextState)
		{
		case StateMenu:
			currentState = new Menu;
			break;

		case StateGame:
			currentState = new Game("Data/Map.txt", "Data/block.bmp");
			break;
		
		case StateNewHighscore:
			currentState = new NewHighscore("Data/Highscore.txt");
			break;
		
		case StateHighscore:
			currentState = new Highscore("Data/Highscore.txt");
		}
		stateID = nextState;
		nextState = StateNull;
	}
}