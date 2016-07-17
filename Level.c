#include "Level.h"

void init_level(GameState *game, short level)
{
	game->state = PLAY;
	game->level = level;

	//init texture
	game->bgTexture = NULL;
	game->boatTexture = NULL;
	game->moveLabel = NULL;
	game->font = NULL;
	game->helper = NULL;
	for (int i = 0; i < MAX_UNIT; i++)
	{
		game->unitTexture[i] = NULL;
		game->unit[i].unitTexture = NULL;
	}

	//init button
	initButton(game);

	//init pause menu
	init_pausemenu(game);

	//init result
	init_result(game);
	game->game_result = OVER;

	if (game->level == 1)
	{
		load_level_1(game);
	}
	else if (game->level == 2)
	{
		//SET LEVEL 2 HERE.
	}

	//set seat position
	for (int i = 0; i < game->level_seat; i++)
	{
		game->boat.seat[i][x] = game->boat.x + 100 + 50 * i;
		game->boat.seat[i][y] = game->boat.y + 0;
		game->boat.seat[i][FREE_SEAT] = 1;
	}
}

void close_level(GameState *game)
{
	//clear all texture memory
	if (game->bgTexture != NULL) SDL_DestroyTexture(game->bgTexture);
	if (game->boatTexture != NULL) SDL_DestroyTexture(game->boatTexture);

	for (int i = 0; i < MAX_UNIT; i++)
	{
		if (game->unitTexture[i] != NULL) SDL_DestroyTexture(game->unitTexture[i]);
		if (game->unit[i].unitTexture != NULL) SDL_DestroyTexture(game->unit[i].unitTexture);
	}

	if (game->font != NULL) TTF_CloseFont(game->font);
	if (game->helper != NULL) SDL_DestroyTexture(game->helper);

	//set texture
	game->bgTexture = NULL;
	game->boatTexture = NULL;
	game->moveLabel = NULL;
	game->font = NULL;

	for (int i = 0; i < MAX_UNIT; i++)
	{
		game->unit[i].unitTexture = NULL;
	}

	//close result
	close_result(game);

	//close pause menu
	close_pausemenu(game);

	//close button
	closeButton(game);
}