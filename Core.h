#include "main.h"
#include "Button.h"
#include "PauseMenu.h"
#include "BGM.h"

void initGame(GameState *game);
void closeGame(GameState *game);

void processEvent(GameState *game);
void processGame(GameState *game);
void renderGame(GameState *game);

void ToggleFullscreen(SDL_Window* Window);
