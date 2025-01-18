#ifndef STRUCTS_H
#define STRUCTS_H

#include "common.h"

struct PlayerStruct {
	SDL_Texture *playerTexture;
	SDL_Rect positionRect;
	float vel_y;
	int test;
};

struct PipeStruct {
	SDL_Texture *pipeTexture;
	SDL_Rect topPositionRect;
	SDL_Rect bottomPositionRect;
	int gap;
};

struct AudioAssets {
};

struct GameState {
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool gameIsRunning;
	bool gameIsPaused;
};

#endif
