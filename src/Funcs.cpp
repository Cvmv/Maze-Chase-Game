#include "Funcs.h"
//#include <SDL2/SDL_surface.h>

bool collision(const SDL_Rect *rec1, const SDL_Rect *rec2)
{
	if(rec1->y >= rec2->y + rec2->h)	// oben dr�ber
		return 0;
	if(rec1->x >= rec2->x + rec2->w)	// rechts daneben
		return 0;
	if(rec1->y + rec1->h <= rec2->y)	// unten drunter 
		return 0;
	if(rec1->x + rec1->w <= rec2->x)	// links daneben
		return 0;
	return 1;							// KOLLISION!!!!!
}

bool collision(int x, int y, const SDL_Rect *rec2)
{
	if(y >= rec2->y + rec2->h)	// unten drunter
		return 0;
	if(x >= rec2->x + rec2->w)	// rechts daneben
		return 0;
	if(y <= rec2->y)			// dr�ber 
		return 0;
	if(x <= rec2->x)			// links daneben
		return 0;
	return 1;					// KOLLISION!!!!!
}

bool loadFiles()
{
	//font = TTF_OpenFont("Data/DejaVuSans.ttf", 28);
	font = TTF_OpenFont(fontname.c_str(), 28);
	if(font == NULL) {
		cout << "Error: Font could not be created!" << endl;
		return false;
	}
	return true;
}
bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	if(TTF_Init() == -1)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	screen = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
	gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	/*gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);*/
	screen = SDL_GetWindowSurface(gWindow);
	if (screen == NULL)
		printf("Screen could not be created! SDL Error: %s\n", SDL_GetError());
	//cout << "init" << endl;
	return true;
}
void cleanUp()
{
	delete currentState;
	//SDL_FreeSurface(screen);
	TTF_CloseFont(font);
	//SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

SDL_Rect makeRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}