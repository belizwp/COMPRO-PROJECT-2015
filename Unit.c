#include "Unit.h"

enum { x, y, FREE_SEAT };

void updateUnit(GameState *game)
{
	for (int i = 0; i < game->level_unit; i++)
	{
		//hover & click check
		if (game->mx >= game->unit[i].x && game->mx <= game->unit[i].x + game->unit[i].w &&
			game->my >= game->unit[i].y && game->my <= game->unit[i].y + game->unit[i].h && 
			!game->boat.moving && game->pressed)
		{
			game->pressed = 0;
			printf("CLick unit %d, weight = %d\n", i, game->unit[i].weight);
			printf("total unit move %d\n", game->unit_move);
			//set unit on right side to boat
			if (game->unit[i].pos == game->boat.side)
			{
				//set unit to boat
				for (int j = 0; j < game->level_seat; j++)
				{
					if (game->boat.seat[j][FREE_SEAT])
					{
						game->unit_move++;

						if (game->unit[i].pos == RIGHT) game->land.r_unit--;
						else if (game->unit[i].pos == LEFT) game->land.l_unit--;

						game->boat.current_weight += game->unit[i].weight;

						game->boat.seat[j][FREE_SEAT] = 0;
						game->unit[i].x = game->boat.seat[j][x];
						game->unit[i].y = game->boat.seat[j][y];
						game->unit[i].pos = ONBOAT;
						game->unit[i].seat = j;
						break;
					}
				}
			}
			//set unit on boat to land
			else if (game->unit[i].pos == ONBOAT)
			{
				game->unit_move++;

				game->boat.current_weight -= game->unit[i].weight;

				if (game->unit[i].side == RIGHT)
				{
					game->boat.seat[game->unit[i].seat][FREE_SEAT] = 1;
					game->unit[i].x = game->land.r_pos[i][x];
					game->unit[i].y = game->land.r_pos[i][y];
					game->unit[i].pos = RIGHT;

					game->land.r_unit++;
				}
				else if (game->unit[i].side == LEFT)
				{
					game->boat.seat[game->unit[i].seat][FREE_SEAT] = 1;
					game->unit[i].x = game->land.l_pos[i][x];
					game->unit[i].y = game->land.l_pos[i][y];
					game->unit[i].pos = LEFT;

					game->land.l_unit++;
				}
			}

			printf("l_land %d unit\nr_land %d unit\n", game->land.l_unit, game->land.r_unit);
		}
	}
}

void drawUnit(GameState *game)
{
	for (int i = 0; i < game->level_unit; i++)
	{
		//create rect
		SDL_Rect unit = { game->unit[i].x, game->unit[i].y, game->unit[i].w, game->unit[i].h };
		SDL_RenderCopy(game->renderer, game->unit[i].unitTexture, NULL, &unit);
	}
}