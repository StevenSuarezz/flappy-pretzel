#include "init.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "defs.h"
#include "util.h"

int initPlayerStruct(struct PlayerStruct *player, int x, int y) {
	if (player == NULL) {
		printf("initPlayerStruct was passed a nullptr for player\n");
		return -1;
	}

	player->textureRect.x = x;
	player->textureRect.y = y;
	player->textureRect.w = PLAYER_TEXTURE_WIDTH;
	player->textureRect.h = PLAYER_TEXTURE_HEIGHT;

	player->collisionRect.x = x + PLAYER_HITBOX_LEFT_OFFSET;
	player->collisionRect.y = y + PLAYER_HITBOX_TOP_BOTTOM_OFFSET;
	player->collisionRect.w = PLAYER_TEXTURE_WIDTH - PLAYER_HITBOX_LEFT_OFFSET - PLAYER_HITBOX_RIGHT_OFFSET;
	player->collisionRect.h = PLAYER_TEXTURE_HEIGHT - (2 * PLAYER_HITBOX_TOP_BOTTOM_OFFSET);

	player->vel_y = 0.0f;
	player->angle = 0.0f;

	return 0;
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

int initGame(struct Game *game) {
	game->window = SDL_CreateWindow("Flappy Pretzel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (game->window == NULL) {
		printf("could not create window: %s\n", SDL_GetError());
		return -1;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
	if (game->renderer == NULL) {
		printf("Could not create renderer: %s\n", SDL_GetError());
		return -1;
	}

	game->score = 0;

	game->isRunning = true;
	game->isPaused = false;
	return 0;
}

int initSubsystems() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("could not initialize SDL2: %s\n", SDL_GetError());
		return -1;
	}

	if (Mix_Init(MIX_INIT_MP3) < 0) {
		printf("Could not initialize SDL mixer: %s\n", Mix_GetError());
		return -1;
	}

	if (TTF_Init() < 0) {
		printf("Could not initialize TTF: %s\n", TTF_GetError());
		return -1;
	}

	return 0;
}

void initPipeStructs(struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	setPipeOffScreen(pipe1, 0);
	setPipeOffScreen(pipe2, 700);
}
