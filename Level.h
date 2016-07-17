#pragma once
#include "Main.h"
#include "Result.h"
#include "Button.h"
#include "PauseMenu.h"
#include "Level_1.h"

enum { x, y, FREE_SEAT }; //set up position

void init_level(GameState *game, short level);
void close_level(GameState *game);