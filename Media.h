#pragma once
#include "main.h"

SDL_Texture* loadIMGTexture(char *path, SDL_Renderer *renderer);
TTF_Font* loadFont(char *file, int ptsize);
SDL_Texture* drawtext(char text[], TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA, SDL_Renderer *renderer);
