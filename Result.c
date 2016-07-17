#include "Result.h"

#define NUM_BUTTON 3

void init_result(GameState *game)
{
	game->result.alpha = 0;
	game->result.bgResult = IMG_LoadTexture(game->renderer, "Images\\tran_black.png");
	game->result.gamePassTexture = IMG_LoadTexture(game->renderer, "Images\\you_win.png");

	//set each button
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		if (i == 0)
		{
			game->result.btn[i].type = GOTO_MENU;
			game->result.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_menu.png");
		}
		else if (i == 1)
		{
			game->result.btn[i].type = REPLAY;
			game->result.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_playagain.png");
		}
		else if (i == 2)
		{
			game->result.btn[i].type = QUIT;
			game->result.btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_quit.png");
		}

		game->result.btn[i].state = 0;

		//set button dimension
		game->result.btn[i].x = (SCREEN_WIDTH - 200) / 2;
		game->result.btn[i].y = 350 + (i * 105);
		game->result.btn[i].w = 200;
		game->result.btn[i].h = 100;
		
		//set button sprite
		game->result.btn[i].rect[0].x = 0;
		game->result.btn[i].rect[0].y = 0;
		game->result.btn[i].rect[0].w = 200;
		game->result.btn[i].rect[0].h = 100;

		game->result.btn[i].rect[1].x = 200;
		game->result.btn[i].rect[1].y = 0;
		game->result.btn[i].rect[1].w = 200;
		game->result.btn[i].rect[1].h = 100;
	}
}

void close_result(GameState *game)
{
	SDL_DestroyTexture(game->result.bgResult);
	SDL_DestroyTexture(game->result.gamePassTexture);

	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_DestroyTexture(game->result.btn[i].texture);
	}
}

void updateResult(GameState *game)
{
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		game->result.btn[i].state = 0;

		if (game->mx >= game->result.btn[i].x && game->mx <= game->result.btn[i].x + game->result.btn[i].w &&
			game->my >= game->result.btn[i].y && game->my <= game->result.btn[i].y + game->result.btn[i].h)
		{
			game->result.btn[i].state = 1;
		}

		if (game->result.btn[i].state == 1 && game->pressed)
		{
			game->pressed = 0;

			if (game->result.btn[i].type == REPLAY)
			{
				close_level(game);
				init_level(game, game->level); //replay level
			}
			else if (game->result.btn[i].type == QUIT)
			{
				close_level(game);
				game->quit = 1;
			}
			else if (game->result.btn[i].type == GOTO_MENU)
			{
				close_level(game);
				init_menu(game);
			}
		}
	}
}

void drawGameResult(GameState *game)
{
	//draw bg
	SDL_SetTextureAlphaMod(game->result.bgResult, (game->result.alpha + 10 < 255 ? game->result.alpha += 10 : game->result.alpha));
	SDL_RenderCopy(game->renderer, game->result.bgResult, NULL, NULL);

	//draw flag
	if (game->game_result == WIN)
	{
		SDL_Rect rect = { (SCREEN_WIDTH - 600) / 2, 100, 600, 200 };
		SDL_RenderCopy(game->renderer, game->result.gamePassTexture, NULL, &rect);
	}
	else if (game->game_result == OVER)
	{
		SDL_Rect rect = { (SCREEN_WIDTH - 600) / 2, 100, 600, 200 };
		SDL_RenderCopy(game->renderer, game->result.gameOverTexture, NULL, &rect);
	}

	//draw button
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_Rect rect = { game->result.btn[i].x, game->result.btn[i].y, game->result.btn[i].w, game->result.btn[i].h };
		SDL_RenderCopy(game->renderer, game->result.btn[i].texture, &game->result.btn[i].rect[game->result.btn[i].state], &rect);
	}
}