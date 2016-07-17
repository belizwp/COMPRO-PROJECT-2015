#include "Menu.h"
#include "stdio.h"

#define NUM_BUTTON 2

void init_menu(GameState *game)
{
	game->state = MAIN_MENU;

	game->menu.bg = IMG_LoadTexture(game->renderer, "Images\\bg_menu.png");

	for (short i = 0; i < NUM_BUTTON; i++)
	{
		if (i == 0)
		{
			game->menu.btn[i].type = START;
			game->menu.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_play.png");
		}
		else if (i == 1)
		{
			game->menu.btn[i].type = QUIT;
			game->menu.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_quit.png");
		}
		

		game->menu.btn[i].state = 0;

		//set button dimension
		game->menu.btn[i].x = (SCREEN_WIDTH - 200) / 2;
		game->menu.btn[i].y = (SCREEN_HEIGHT - 100 * NUM_BUTTON) / 2 + (i * 105);
		game->menu.btn[i].w = 200;
		game->menu.btn[i].h = 100;

		//set button sprite
		game->menu.btn[i].rect[0].x = 0;
		game->menu.btn[i].rect[0].y = 0;
		game->menu.btn[i].rect[0].w = 200;
		game->menu.btn[i].rect[0].h = 100;

		game->menu.btn[i].rect[1].x = 200;
		game->menu.btn[i].rect[1].y = 0;
		game->menu.btn[i].rect[1].w = 200;
		game->menu.btn[i].rect[1].h = 100;
	}

}

void close_menu(GameState *game)
{
	SDL_DestroyTexture(game->menu.bg);

	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_DestroyTexture(game->menu.btn[i].texture);
	}
}

void updateMenu(GameState *game)
{
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		game->menu.btn[i].state = 0;

		if (game->mx >= game->menu.btn[i].x && game->mx <= game->menu.btn[i].x + game->menu.btn[i].w &&
			game->my >= game->menu.btn[i].y && game->my <= game->menu.btn[i].y + game->menu.btn[i].h)
		{
			game->menu.btn[i].state = 1;
		}

		if (game->menu.btn[i].state == 1 && game->pressed)
		{
			game->pressed = 0;

			if (game->menu.btn[i].type == START)
			{
				close_menu(game);
				init_level(game, 1);
			}
			else if (game->menu.btn[i].type == QUIT)
			{
				game->quit = 1;
			}
		}
	}
}

void drawMenu(GameState *game)
{
	//draw bg
	SDL_RenderCopy(game->renderer, game->menu.bg, NULL, NULL);

	//draw button
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_Rect rect = { game->menu.btn[i].x, game->menu.btn[i].y, game->menu.btn[i].w, game->menu.btn[i].h };
		SDL_RenderCopy(game->renderer, game->menu.btn[i].texture, &game->menu.btn[i].rect[game->menu.btn[i].state], &rect);
	}
}
