#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "audio.h"
#include "common.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "update.h"
#include "util.h"

void freeTextures(struct PlayerStruct *player, struct GameAssets *gameAssets) {
	SDL_DestroyTexture(player->playerTexture);
	SDL_DestroyTexture(gameAssets->backgroundTexture);
}

int main(int argc, char *args[]) {
	struct GameState gameState = {0};
	struct GameAssets gameAssets = {0};
	struct PlayerStruct player = {0};
	struct PipeStruct pipe1 = {0};
	struct PipeStruct pipe2 = {0};

	double deltaTime = 0.0f;
	Uint64 lastTime = SDL_GetTicks64();
	Uint64 frameStart;
	int frameTime;

	srand(time(NULL));

	if (initSubsystems() < 0) {
		printf("Subsytems failed to initalize...\n");
		return -1;
	}

	if (initGameState(&gameState) < 0) {
		printf("Failed to initialize gameState\n");
		return -1;
	}

	if (initGameTextures(gameState.renderer, &player.playerTexture, &gameAssets.backgroundTexture, &pipe1.pipeTexture, &pipe2.pipeTexture) < 0) {
		printf("Error initializing game textures\n");
		printf("Are you running game from the build dir as stated in the README instructions?\n");
		return -1;
	}

	if (initAudioAssets(&gameAssets) < 0) {
		printf("Failed to initialize game assets struct\n");
		return -1;
	}

	if (initPlayerStruct(&player) < 0) {
		printf("Failed to initialize player struct...\n");
		return -1;
	}

	initPipeStructs(&pipe1, &pipe2);

	// Main game loop
	gameState.isRunning = true;
	while (gameState.isRunning) {
		// ====================================== Input Phase
		doInput(&gameState, &player);

		// ====================================== Update Phase
		update(&gameState, &gameAssets, &player, &pipe1, &pipe2, deltaTime);

		// ====================================== Render Phase
		render(&gameState, &gameAssets, &player, &pipe1, &pipe2);

		// ====================================== Cap frame rate
		// printf("DELTA TIME: %f\n", deltaTime);
		capFrameRate(&frameStart, &lastTime, &deltaTime, &frameTime);
	}

	freeTextures(&player, &gameAssets);
	Mix_FreeMusic(gameAssets.audioAssets.backgroundMusic);
	Mix_FreeChunk(gameAssets.audioAssets.pretzelSFX1);
	SDL_DestroyRenderer(gameState.renderer);
	SDL_DestroyWindow(gameState.window);
	SDL_Quit();
	return 0;
}
