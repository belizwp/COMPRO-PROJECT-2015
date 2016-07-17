#include "Logic.h"

short moveBoatCheck(GameState *game)
{
	if (game->level == 1)
	{
		return mov_boat_level_1(game);
	}
	else
	{
		return 0;
	}
}

void gameEndCheck(GameState *game)
{
	if (game->land.l_unit == game->level_unit)
	{
		printf("==== GAME WIN ====\n");
		printf("TOTAL BOAT MOVE : %d\n", game->move);
		printf("TOTAL UNIT MOVE : %d\n", game->unit_move);
		Mix_PlayChannel(-1, game->win_effect, 0);

		//game->time = 1;
		game->result.alpha = 0;
		game->game_result = WIN;
		game->state = RESULT;
	}
}

void midRiverCheck(GameState *game)
{
	if (game->boat.x == (SCREEN_WIDTH - game->boat.w) / 2)
	{
		printf("boat in the middle of river\n");

		if (game->level == 1)
		{
			mid_river_level_1(game);
		}
	}
}
