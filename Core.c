#include "core.h"

void processEvent(GameState *game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game->quit = 1;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			game->keydown = 1;

			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				if (game->state == PLAY) game->state = PAUSE_MENU;
				else if (game->state == PAUSE_MENU || game->state == HELPER) game->state = PLAY;
			}
			else if (e.key.keysym.sym == SDLK_F11)
			{
				ToggleFullscreen(game->window);
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			game->keydown = 0;
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&game->mx, &game->my);
			//printf("%d, %d\n", game->mx, game->my);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				game->pressed = 1;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				game->pressed = 0;
			}
		}
	}
}

void processGame(GameState *game)
{ 
	game->time++;

	if (game->state == MAIN_MENU)
	{
		updateMenu(game);
	}
	else if (game->state == PLAY)
	{
		updateBoat(game);
		updateUnit(game);
		updateButton(game);
		midRiverCheck(game);

		//check number of unit on left side
		gameEndCheck(game);
	}
	else if (game->state == RESULT)
	{
		updateResult(game);
	}
	else if (game->state == PAUSE_MENU || game->state == HELPER)
	{
		updatePauseMenu(game);
	}
}

void renderGame(GameState *game)
{
	//clear screen
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	if (game->state == MAIN_MENU)
	{
		drawMenu(game);
	}
	else if (game->state == PLAY || game->state == RESULT || game->state == PAUSE_MENU || game->state == HELPER)
	{
		//draw bg
		SDL_RenderCopy(game->renderer, game->bgTexture, NULL, NULL);

		//draw unit
		drawUnit(game);

		//draw boat
		drawBoat(game);

		//draw text
		//char str[100] = "";
		//sprintf_s(str, 100, "%d", game->unit_move);
		//game->moveLabel = drawtext(str, game->font, 0, 0, 0, 255, game->renderer);
		//SDL_QueryTexture(game->moveLabel, NULL, NULL, &game->moveLabelW, &game->moveLabelH);
		//SDL_Rect text = { (SCREEN_WIDTH - game->moveLabelW) / 2, 100, game->moveLabelW, game->moveLabelH };
		//SDL_RenderCopy(game->renderer, game->moveLabel, NULL, &text);
		//SDL_DestroyTexture(game->moveLabel);

		drawButton(game);

		if (game->state == RESULT)
		{
			//draw result
			drawGameResult(game);
		}

		if (game->state == PAUSE_MENU || game->state == HELPER)
		{
			drawPauseMenu(game);
		}
	}

	//show
	SDL_RenderPresent(game->renderer);
}

void initGame(GameState *game)
{
	//set status
	game->time = 0;
	game->pressed = 0;
	game->keydown = 0;
	game->bgm_mute = 0;

	init_BGM(game);
	init_menu(game);
}

void closeGame(GameState *game)
{
	SDL_DestroyWindow(game->window);
	SDL_DestroyRenderer(game->renderer);

	close_BGM(game);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void ToggleFullscreen(SDL_Window* Window) 
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	//SDL_ShowCursor(IsFullscreen);
}