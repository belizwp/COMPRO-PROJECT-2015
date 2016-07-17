#include "Button.h"

#define NUM_BUTTON 3 //pause, help, sound

void initButton(GameState *game)
{
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		game->btn[i].texture = NULL;

		if (i == 0)
		{
			game->btn[i].type = PAUSE;
			game->btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_more.png");
		}
		else if (i == 1)
		{
			game->btn[i].type = HELP;
			game->btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_help.png");
		}
		else if (i == 2)
		{
			game->btn[i].type = MUTE;
			game->btn[i].texture = IMG_LoadTexture(game->renderer, "Images\\btn_mute.png");
		}


		game->btn[i].state = 0;

		//set button dimension
		game->btn[i].x = 50 + (65 * i);
		game->btn[i].y = 50;
		game->btn[i].w = 60;
		game->btn[i].h = 60;

		//set button sprite
		game->btn[i].rect[0].x = 0;
		game->btn[i].rect[0].y = 0;
		game->btn[i].rect[0].w = 100;
		game->btn[i].rect[0].h = 100;

		game->btn[i].rect[1].x = 100;
		game->btn[i].rect[1].y = 0;
		game->btn[i].rect[1].w = 100;
		game->btn[i].rect[1].h = 100;
	}
}

void closeButton(GameState *game)
{
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_DestroyTexture(game->btn[i].texture);
	}
}

void updateButton(GameState *game)
{
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		game->btn[i].state = 0;

		if (game->btn[i].type == MUTE)
		{
			if (Mix_PausedMusic() == 1)
			{
				game->btn[i].state = 1;
			}
		}

		if (game->mx >= game->btn[i].x && game->mx <= game->btn[i].x + game->btn[i].w &&
			game->my >= game->btn[i].y && game->my <= game->btn[i].y + game->btn[i].h)
		{
			game->btn[i].state = 1;
		}

		if (game->btn[i].state == 1 && game->pressed)
		{
			game->pressed = 0;

			if (game->btn[i].type == PAUSE)
			{
				game->state = PAUSE_MENU;
			}
			else if (game->btn[i].type == HELP)
			{
				game->state = HELPER;
			}
			else if (game->btn[i].type == MUTE)
			{
				if (game->mx >= game->btn[i].x && game->mx <= game->btn[i].x + game->btn[i].w &&
					game->my >= game->btn[i].y && game->my <= game->btn[i].y + game->btn[i].h)
				{
					//If the music is paused
					if (Mix_PausedMusic() == 1)
					{
						//Resume the music
						Mix_ResumeMusic();
					}
					//If the music is playing
					else
					{
						//Pause the music
						Mix_PauseMusic();
					}
				}
			}
		}
	}
}

void drawButton(GameState *game)
{
	//draw button
	for (short i = 0; i < NUM_BUTTON; i++)
	{
		SDL_Rect rect = { game->btn[i].x, game->btn[i].y, game->btn[i].w, game->btn[i].h };
		SDL_RenderCopy(game->renderer, game->btn[i].texture, &game->btn[i].rect[game->btn[i].state], &rect);
	}
}