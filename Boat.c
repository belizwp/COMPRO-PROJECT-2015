#include "Boat.h"

void moveBoat(GameState *game)
{
	//move boat to L/R
	if (game->boat.x >= 100 && game->boat.side == RIGHT)
	{
		game->boat.x -= 8;
	}
	else if (game->boat.x <= SCREEN_WIDTH - 100 && game->boat.side == LEFT)
	{
		game->boat.x += 8;
	}

	if (game->boat.x <= 100)
	{
		printf("boat board left\n");
		game->boat.moving = 0;
		game->boat.side = LEFT;
	}
	if (game->boat.x >= SCREEN_WIDTH - 100 - game->boat.w)
	{
		printf("boat board right\n");
		game->boat.moving = 0;
		game->boat.side = RIGHT;
	}

	//update boat seat position
	for (int i = 0; i < game->level_seat; i++)
	{
		game->boat.seat[i][x] = game->boat.x + 100 + 50 * i;
		game->boat.seat[i][y] = game->boat.y + 0;
	}

	//update unit positon on boat
	for (int i = 0; i < game->level_unit; i++)
	{
		if (game->unit[i].pos == ONBOAT)
		{
			game->unit[i].side = game->boat.side;
			game->unit[i].x = game->boat.seat[game->unit[i].seat][0];
		}
	}
}

void updateBoat(GameState *game)
{
	if (game->boat.moving)
	{
		moveBoat(game);
	}

	else if (game->mx >= game->boat.x && game->mx <= game->boat.x + game->boat.w &&
			 game->my >= game->boat.y + game->boat.h / 2 && game->my <= game->boat.y + game->boat.h && game->pressed)
	{
		game->pressed = 0;
		printf("CLick boat\n");
		if (moveBoatCheck(game))
		{
			printf("boat is moving\n");
			game->boat.moving = 1;
			game->move++;
			printf("total boat move = %d\n", game->move);
		}
	}
}

void drawBoat(GameState *game)
{
	SDL_Rect boat = { game->boat.x, game->boat.y, game->boat.w, game->boat.h };
	SDL_RenderCopy(game->renderer, game->boatTexture, NULL, &boat);
}