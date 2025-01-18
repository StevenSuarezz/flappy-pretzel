#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "common.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FPS 60
#define GRAVITY 9.81f

const int FRAME_DELAY = 1000 / FPS;
const float JUMP_FORCE = -7.0f;
const float FALL_MULTIPLIER = 1.75f;
const float PLAYER_ANGLE_MULTIPLIER = 3.5f;
const int PIPE_SPEED = 3;
const int PIPE_WIDTH = 100;

const int BACKGROUND_VOLUME_LEVEL = 10;

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

void freeTextures(struct PlayerStruct *player, SDL_Texture *backgroundTexture) {
	SDL_DestroyTexture(player->playerTexture);
	SDL_DestroyTexture(backgroundTexture);
}

void initPlayerStruct(struct PlayerStruct *player) {
	player->positionRect.x = SCREEN_WIDTH / 3 - 70;
	player->positionRect.y = SCREEN_HEIGHT / 2 - 50;
	player->positionRect.w = 320 / 5;
	player->positionRect.h = 196 / 5;

	player->vel_y = 0.0f;
}

void setPipeOffScreen(struct PipeStruct *pipe1, int x_offset) {
	// Create a gap of at least 100px and add a random amount to it clamped to
	// 64px
	pipe1->gap = (rand() % 64) + 100;

	// Recall that SCREEN_HEIGHT = 480
	int top_min = -440;
	int top_max = -164;
	int top_y = rand() % (top_max - top_min + 1) + top_min;

	int bot_y = top_y + SCREEN_HEIGHT + pipe1->gap;

	pipe1->topPositionRect.x = SCREEN_WIDTH + x_offset;
	pipe1->topPositionRect.y = top_y;
	pipe1->topPositionRect.w = PIPE_WIDTH;
	pipe1->topPositionRect.h = SCREEN_HEIGHT;

	pipe1->bottomPositionRect.x = pipe1->topPositionRect.x;
	pipe1->bottomPositionRect.y = bot_y;
	pipe1->bottomPositionRect.w = PIPE_WIDTH;
	pipe1->bottomPositionRect.h = SCREEN_HEIGHT;
}

void updatePipeStructs(struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	pipe1->topPositionRect.x = pipe1->topPositionRect.x - PIPE_SPEED;
	pipe1->bottomPositionRect.x = pipe1->topPositionRect.x;
	pipe2->topPositionRect.x = pipe2->topPositionRect.x - PIPE_SPEED;
	pipe2->bottomPositionRect.x = pipe2->topPositionRect.x;

	// Check if pipe is off of screen
	if (pipe1->topPositionRect.x < -PIPE_WIDTH) {
		printf("DEBUG: Pipe1 is off the screen... resetting\n");
		setPipeOffScreen(pipe1, 0);
	} else if (pipe2->topPositionRect.x < -PIPE_WIDTH) {
		printf("DEBUG: Pipe2 is off the screen... resetting\n");
		setPipeOffScreen(pipe2, 0);
	}
}

// Load assets into surfaces and create textures from those surfaces
int initGameTextures(SDL_Renderer *renderer, SDL_Texture **playerTexture, SDL_Texture **backgroundTexture, SDL_Texture **pipe1Texture, SDL_Texture **pipe2Texture) {
	// Player
	SDL_Surface *playerSurface = IMG_Load("../assets/images/pretzel.png");
	if (playerSurface == NULL) {
		printf("Error loading player surface: %s\n", IMG_GetError());
		return -1;
	}

	*playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
	SDL_FreeSurface(playerSurface);

	// Background
	SDL_Surface *backgroundSurface = IMG_Load("../assets/images/background.png");
	if (backgroundSurface == NULL) {
		printf("Error loading background surface: %s\n", IMG_GetError());
		return -1;
	}

	*backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_FreeSurface(backgroundSurface);

	// Pipes
	SDL_Surface *pipeSurface = IMG_Load("../assets/images/pipe.png");
	if (pipeSurface == NULL) {
		printf("Error loading pipe surface: %s\n", IMG_GetError());
		return -1;
	}

	*pipe1Texture = SDL_CreateTextureFromSurface(renderer, pipeSurface);
	*pipe2Texture = SDL_CreateTextureFromSurface(renderer, pipeSurface);
	SDL_FreeSurface(pipeSurface);

	return 0;
}

// TODO: First function that is a bool - lets either make all other functions a bool or make it return an int classic c style
bool detectCollision(struct PlayerStruct *player, struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	if (SDL_HasIntersection(&player->positionRect, &pipe1->topPositionRect) || SDL_HasIntersection(&player->positionRect, &pipe1->bottomPositionRect)) {
		printf("COLLISION WITH PIPE 1 HOLY SHIT\n");
		return true;
	} else if (SDL_HasIntersection(&player->positionRect, &pipe2->topPositionRect) || SDL_HasIntersection(&player->positionRect, &pipe2->bottomPositionRect)) {
		printf("COLLISION WITH PIPE 2 HOLY SHIT\n");
		return true;
	}
	return false;
}

void drawDebugRects(SDL_Renderer *renderer, struct PlayerStruct *player, struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	SDL_RenderDrawRect(renderer, &player->positionRect);
	SDL_RenderDrawRect(renderer, &pipe1->topPositionRect);
	SDL_RenderDrawRect(renderer, &pipe1->bottomPositionRect);
	SDL_RenderDrawRect(renderer, &pipe2->topPositionRect);
	SDL_RenderDrawRect(renderer, &pipe2->bottomPositionRect);
}

int main(int argc, char *args[]) {
	SDL_Texture *backgroundTexture;

	struct PlayerStruct player = {0};
	struct PipeStruct pipe1 = {0};
	struct PipeStruct pipe2 = {0};

	float pipeVel = 0.5f;

	srand(time(NULL));

	Mix_Music *gameMusic = NULL;
	Mix_Chunk *pretzelSFX1 = NULL;
	Mix_Chunk *pretzelSFX2 = NULL;
	Mix_Chunk *pretzelSFX3 = NULL;
	Mix_Chunk *pretzelSFX4 = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("could not initialize sdl2: %s\n", SDL_GetError());
		return -1;
	}
	window = SDL_CreateWindow("Flappy Pretzel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("could not create window: %s\n", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Could not create renderer: %s\n", SDL_GetError());
		return -1;
	}

	if (initGameTextures(renderer, &player.playerTexture, &backgroundTexture, &pipe1.pipeTexture, &pipe2.pipeTexture) < 0) {
		printf("Error initializing game textures\n");
		printf("Are you running game from the build dir as stated in the README instructions?\n");
		return -1;
	}

	if (Mix_Init(MIX_INIT_MP3) < 0) {
		printf("Could not initialize SDL mixer: %s\n", Mix_GetError());
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	gameMusic = Mix_LoadMUS("../assets/sound/main-music.mp3");
	if (gameMusic == NULL) {
		printf("Failed to load background music: %s\n", Mix_GetError());
		return -1;
	}

	pretzelSFX1 = Mix_LoadWAV("../assets/sound/pretzel1.mp3");
	if (pretzelSFX1 == NULL) {
		printf("Failed to load pretzelSFX1: %s\n", Mix_GetError());
		return -1;
	}

	if (Mix_VolumeMusic(BACKGROUND_VOLUME_LEVEL) < 0) {
		printf("Failed to reduce music: %s\n", Mix_GetError());
		return -1;
	}

	if (Mix_PlayMusic(gameMusic, -1) < 0) {
		printf("Failed to start playing background music: %s\n", Mix_GetError());
		return -1;
	}

	initPlayerStruct(&player);

	setPipeOffScreen(&pipe1, 0);
	setPipeOffScreen(&pipe2, 350);

	Uint64 lastTime = SDL_GetTicks64();
	Uint64 frameStart;
	int frameTime;

	double playerAngle = 0.0f;

	// Main game loop
	while (gameIsRunning) {
		// ============= Input Phase
		doInput();
		// ============= Update Phase
		frameStart = SDL_GetTicks64();
		double deltaTime = (frameStart - lastTime) / 1000.0f;
		lastTime = frameStart;
		// printf("DELTA TIME: %f\n", deltaTime);

		if (!gameIsPaused) {
			if (detectCollision(&player, &pipe1, &pipe2) && Mix_Playing(0) == 0) {
				Mix_PlayChannel(0, pretzelSFX1, 0);
			}
			// Update player
			player.vel_y += GRAVITY * FALL_MULTIPLIER * deltaTime;
			printf("Player velocity: %f\n", player.vel_y);
			player.positionRect.y += player.vel_y;
			playerAngle = player.vel_y * PLAYER_ANGLE_MULTIPLIER;

			// Update pipes
			updatePipeStructs(&pipe1, &pipe2);
		}

		// ============ Render Phase
		// Render background
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

		// Render player
		SDL_RenderCopyEx(renderer, player.playerTexture, NULL, &player.positionRect, playerAngle, NULL, SDL_FLIP_NONE);

		// Render pipes
		SDL_RenderCopyEx(renderer, pipe1.pipeTexture, NULL, &pipe1.topPositionRect, 0.0f, NULL, SDL_FLIP_VERTICAL);
		SDL_RenderCopy(renderer, pipe1.pipeTexture, NULL, &pipe1.bottomPositionRect);

		SDL_RenderCopyEx(renderer, pipe2.pipeTexture, NULL, &pipe2.topPositionRect, 0.0f, NULL, SDL_FLIP_VERTICAL);
		SDL_RenderCopy(renderer, pipe2.pipeTexture, NULL, &pipe2.bottomPositionRect);

		drawDebugRects(renderer, &player, &pipe1, &pipe2);

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks64() - frameStart;
		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	freeTextures(&player, backgroundTexture);
	Mix_FreeMusic(gameMusic);
	Mix_FreeChunk(pretzelSFX1);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
