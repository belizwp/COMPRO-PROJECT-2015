#include "stdio.h"
#include "main.h"
#include "core.h"

int main(int argc, char* argv[])
{
	SDL_Window *window = NULL;                    // Declare a window
	SDL_Renderer *renderer = NULL;                // Declare a renderer
	GameState game;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);					  
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3);

	window = SDL_CreateWindow("COMPRO PROJECT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	game.window = window;
	game.renderer = renderer;
	game.quit = 0;

	initGame(&game);

	//Main Loop
	while (!game.quit)
	{
		//game.time++;
		processEvent(&game);
		processGame(&game);
		renderGame(&game);

		//don't hurry!
		SDL_Delay(10);
	}

	closeGame(&game);

	return 0;
}
