#include "stdio.h"
#include "main.h"
#include "media.h"

SDL_Texture* loadIMGTexture(char *path, SDL_Renderer *renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

TTF_Font* loadFont(char* file, int ptsize)
{
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL) {
		printf("Unable to load font: %s %s \n", file, TTF_GetError());
		// Handle the error here.
	}
	return tmpfont;
}

SDL_Texture* drawtext(char text[], TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA, SDL_Renderer *renderer)
{
	SDL_Texture* newTexture = NULL;

	SDL_Color tmpfontcolor = { fgR,fgG,fgB,fgA };
	SDL_Surface* resulting_text = NULL;

	if (fonttodraw != NULL)
	{
		resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);
	}

	newTexture = SDL_CreateTextureFromSurface(renderer, resulting_text);
	SDL_FreeSurface(resulting_text);

	return newTexture;
}
