#include "PauseMenu.h"

#define NUM_BUTTON 3

void init_pausemenu(GameState *game)
{
	game->pause.alpha = 0;
	game->pause.bgPause = IMG_LoadTexture(game->renderer, "Images\\tran_black.png");
	game->pause.helper = game->helper;

	//set each button
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		//if (i == 0)
		//{
		//	game->pause.btn[i].type = RESUME;
		//	game->pause.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_resume.png");
		//}
		if (i == 0)
		{
			game->pause.btn[i].type = REPLAY;
			game->pause.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_playagain.png");
		}
		else if (i == 1)
		{
			game->pause.btn[i].type = GOTO_MENU;
			game->pause.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_menu.png");
		}
		else if (i == 2)
		{
			game->pause.btn[i].type = QUIT;
			game->pause.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_quit.png");
		}

		game->pause.btn[i].state = 0;

		//set button dimension
		game->pause.btn[i].x = (SCREEN_WIDTH - 200) / 2;
		game->pause.btn[i].y = (SCREEN_HEIGHT - 100 * NUM_BUTTON) / 2 + (i * 105);
		game->pause.btn[i].w = 200;
		game->pause.btn[i].h = 100;

		//set button sprite
		game->pause.btn[i].rect[0].x = 0;
		game->pause.btn[i].rect[0].y = 0;
		game->pause.btn[i].rect[0].w = 200;
		game->pause.btn[i].rect[0].h = 100;

		game->pause.btn[i].rect[1].x = 200;
		game->pause.btn[i].rect[1].y = 0;
		game->pause.btn[i].rect[1].w = 200;
		game->pause.btn[i].rect[1].h = 100;
	}
}
void close_pausemenu(GameState *game)
{
	SDL_DestroyTexture(game->pause.bgPause);

	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_DestroyTexture(game->pause.btn[i].texture);
	}
}

void updatePauseMenu(GameState *game)
{
	if (game->state == PAUSE_MENU)
	{
		for (short i = 0; i < NUM_BUTTON; i++)
		{
			game->pause.btn[i].state = 0;

			if (game->mx >= game->pause.btn[i].x && game->mx <= game->pause.btn[i].x + game->pause.btn[i].w &&
				game->my >= game->pause.btn[i].y && game->my <= game->pause.btn[i].y + game->pause.btn[i].h)
			{
				game->pause.btn[i].state = 1;
			}

			if (game->pause.btn[i].state == 1 && game->pressed)
			{
				game->pressed = 0;

				if (game->pause.btn[i].type == REPLAY)
				{
					close_level(game);
					init_level(game, game->level); //replay level
				}
				else if (game->pause.btn[i].type == QUIT)
				{
					close_level(game);
					game->quit = 1;
				}
				else if (game->pause.btn[i].type == GOTO_MENU)
				{
					close_level(game);
					init_menu(game);
				}
				else if (game->pause.btn[i].type == RESUME)
				{
					game->state = PLAY;
				}
			}
		}
	}

	if (game->pressed)
	{
		game->pressed = 0;
		game->state = PLAY;
	}
}

void drawPauseMenu(GameState *game)
{
	//draw bg
	//SDL_SetTextureAlphaMod(game->pause.bgPause, (game->pause.alpha + 10 < 255 ? game->pause.alpha += 10 : game->pause.alpha));
	SDL_RenderCopy(game->renderer, game->pause.bgPause, NULL, NULL);

	if (game->state == PAUSE_MENU)
	{
		//draw button
		for (short i = 0; i < NUM_BUTTON; i++)
		{
			SDL_Rect rect = { game->pause.btn[i].x, game->pause.btn[i].y, game->pause.btn[i].w, game->pause.btn[i].h };
			SDL_RenderCopy(game->renderer, game->pause.btn[i].texture, &game->pause.btn[i].rect[game->pause.btn[i].state], &rect);
		}
	}
	else if (game->state == HELPER)
	{
		SDL_Rect rect = { (SCREEN_WIDTH - 640) / 2, (SCREEN_HEIGHT - 480) / 2, 640, 480 };
		SDL_RenderCopy(game->renderer, game->helper, NULL, &rect);
	}
}
