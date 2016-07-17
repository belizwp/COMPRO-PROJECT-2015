#include "Level_1.h"

enum { FOOL, PEOPLE }; //unit type

void load_level_1(GameState *game)
{
	//set game
	game->move = 0;
	game->unit_move = 0;
	game->level_unit = 7;
	game->level_seat = 3;
	game->land.r_unit = game->level_unit;
	game->land.l_unit = 0;

	//set bg and boat texture
	game->bgTexture = IMG_LoadTexture(game->renderer, "Images\\bg.png");
	game->boatTexture = IMG_LoadTexture(game->renderer, "Images\\boat.png");
	game->helper = IMG_LoadTexture(game->renderer, "Images\\help.png");

	//load font
	game->font = loadFont("arial.ttf", 72);

	//set land and unit position
	for (int i = 0; i < game->level_unit; i++)
	{
		//set poosition on land
		game->land.r_pos[i][x] = 1000 + 50 * i;
		game->land.r_pos[i][y] = 400;

		game->land.l_pos[game->level_unit - i - 1][x] = 50 * i + 20;
		game->land.l_pos[game->level_unit - i - 1][y] = 400;

		//set unit weight and texture
		if (i == 0) {
			game->unit[i].weight = 10;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\10girl.png");
		}
		else if (i == 1)
		{
			game->unit[i].weight = 15;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\15man.png");
		}
		else if (i == 2)
		{
			game->unit[i].weight = 25;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\25man.png");
		}
		else if (i == 3)
		{
			game->unit[i].weight = 40;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\40man.png");
		}
		else if (i == 4)
		{
			game->unit[i].weight = 20;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\20woman.png");
		}
		else if (i == 5)
		{
			game->unit[i].weight = 20;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\20old.png");
		}
		else if (i == 6)
		{
			game->unit[i].weight = 40;
			game->unit[i].unitTexture = IMG_LoadTexture(game->renderer, "Images\\402man.png");
		}

		//set unit type
		if (i == 0 || i == 5 )
		{
			game->unit[i].type = FOOL;
		}
		else
		{
			game->unit[i].type = PEOPLE;
		}

		/*game->unit[i].type = PEOPLE;
		game->unit[i].unitTexture = game->unitTexture[PEOPLE];*/

		//set unit status
		game->unit[i].pos = RIGHT;
		game->unit[i].side = RIGHT;
		game->unit[i].x = game->land.r_pos[i][x];
		game->unit[i].y = game->land.r_pos[i][y];

		//set unit size
		game->unit[i].w = 40;
		game->unit[i].h = 120;


	}
	//set boat carry weight
	game->boat.max_weight = 40;
	game->boat.current_weight = 0;

	//set boat position
	game->boat.w = 350;
	game->boat.h = 200;
	game->boat.x = SCREEN_WIDTH - 100 - game->boat.w;
	game->boat.y = 530;
	game->boat.moving = 0;
	game->boat.side = RIGHT;

}

void mid_river_level_1(GameState *game)
{

}

int mov_boat_level_1(GameState * game)
{
	if (game->boat.current_weight > game->boat.max_weight) return 0;

	short fool = 0;
	short on_boat = 0;

	for (int i = 0; i < game->level_unit; i++)
	{
		if (game->unit[i].pos == ONBOAT)
		{
			on_boat++;
			if (game->unit[i].type == FOOL)
			{
				fool++;
			}
		}
	}

	if (fool == on_boat)
	{
		return 0;
	}

	return 1;
}
