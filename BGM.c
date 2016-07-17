#include "BGM.h"

void init_BGM(GameState *game)
{
	//The music that will be played
	game->bgm = NULL;
	game->win_effect = NULL;

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}

	//Load music
	game->bgm = Mix_LoadMUS("BGM.mp3");
	if (game->bgm == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//Load effect
	game->win_effect = Mix_LoadWAV("win_effect.wav");
	if (game->bgm == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//Play the music
	Mix_PlayMusic(game->bgm, -1);
}

void close_BGM(GameState *game)
{
	//Free the music
	Mix_FreeMusic(game->bgm);
	game->bgm = NULL;

	//Free effect
	Mix_FreeChunk(game->win_effect);
	game->win_effect = NULL;

	Mix_Quit();
}