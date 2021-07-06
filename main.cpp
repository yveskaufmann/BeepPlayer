/**
	Start procedure of the MonoBeepSoundPlayer
	
	Project: MonoBeepSoundPlayer
	File: main.cpp
	Purpose: Initialize the player, choose a song
			 and play the choosed song.

	@author fxdapokalypse
	@version 1.0 11.03.2014
*/

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "SDL2/SDL.h"

#include "BeepPlayer.h"
#include "ExampleSongs.h"
#include "game.h"

using namespace std;

struct Options
{
	char song[256];
};

void argParse(int argc, char **argv, Options *options)
{
	int pos = 0;
	char arg[128];

	strcpy(options->song, "tetris");

	while (pos < argc)
	{
		strcpy(arg, argv[pos]);
		if (strcmp(arg, "--song") == 0 || strcmp(arg, "-s") == 0)
		{
			if (pos + 1 >= argc)
			{
				cerr << "An argument for song is required" << endl;
				exit(1);
			}
			strcpy(options->song, argv[pos + 1]);
			pos++;
		}

		pos++;
	}
}

void quit()
{
	cout << "DEBUG: Quit beep player" << endl;
	BeepPlayer::stop();
	SDL_Quit();
}

/**
	Initialize the player, choose a song and play the choosed song.

	@param argc The count of program arguments.
	@param argv Array with program arguments.

	@return Main Function Return Code
*/
int main(int argc, char *argv[])
{
	Options options;
	argParse(argc, argv, &options);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
	{
		cerr << "Failed to init SDL caused by: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	atexit(quit);

	Game game;
	game.start();

	SDL_Quit();

	return EXIT_SUCCESS;
}
