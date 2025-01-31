#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL_mixer.h"
#include "common.h"

typedef enum {
	PLAYING,
	PAUSED,
	MENU
} State;

struct PlayerStruct {
	SDL_Texture *playerTexture;
	SDL_Rect textureRect;
	SDL_Rect collisionRect;
	float vel_y;
	double angle;
};

struct PipeStruct {
	SDL_Texture *pipeTexture;
	SDL_Rect topPositionRect;
	SDL_Rect bottomPositionRect;
	int gap;
	bool hasScored;
};

struct AudioAssets {
	Mix_Music *backgroundMusic;
	Mix_Chunk *pretzelSFX1;
	Mix_Chunk *pretzelSFX2;
	Mix_Chunk *pretzelSFX3;
	Mix_Chunk *pretzelSFX4;
};

struct ScoreText {
	SDL_Texture *scoreTexture;
	SDL_Rect scorePositionRect;
};

struct GameAssets {
	SDL_Texture *backgroundTexture;
	struct AudioAssets audioAssets;
	struct ScoreText scoreText;
};

struct Game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	State state;
	uint score;
	bool isRunning;
	bool isPaused;
};

#endif
