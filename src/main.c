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

void freeTextures(struct PlayerStruct *player, struct GameAssets *gameAssets) {
	SDL_DestroyTexture(player->playerTexture);
	SDL_DestroyTexture(gameAssets->backgroundTexture);
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

int main(int argc, char *args[]) {
	struct GameState gameState = {0};
	struct GameAssets gameAssets = {0};
	struct PlayerStruct player = {0};
	struct PipeStruct pipe1 = {0};
	struct PipeStruct pipe2 = {0};

	float pipeVel = 0.5f;

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

	setPipeOffScreen(&pipe1, 0);
	setPipeOffScreen(&pipe2, 350);

	Uint64 lastTime = SDL_GetTicks64();
	Uint64 frameStart;
	int frameTime;

	gameState.isRunning = true;
	// Main game loop
	while (gameState.isRunning) {
		// ====================================== Input Phase
		doInput(&gameState, &player);
		// ====================================== Update Phase
		frameStart = SDL_GetTicks64();
		double deltaTime = (frameStart - lastTime) / 1000.0f;
		lastTime = frameStart;
		// printf("DELTA TIME: %f\n", deltaTime);

		if (!gameState.isPaused) {
			if (detectCollision(&player, &pipe1, &pipe2) && Mix_Playing(0) == 0) {
				Mix_PlayChannel(0, gameAssets.audioAssets.pretzelSFX1, 0);
			}
			// Update player
			player.vel_y += GRAVITY * FALL_MULTIPLIER * deltaTime;
			printf("Player velocity: %f\n", player.vel_y);
			player.positionRect.y += player.vel_y;
			player.angle = player.vel_y * PLAYER_ANGLE_MULTIPLIER;

			// Update pipes
			updatePipeStructs(&pipe1, &pipe2);
		}

		// ============ Render Phase
		// Render background
		render(&gameState, &gameAssets, &player, &pipe1, &pipe2);
		frameTime = SDL_GetTicks64() - frameStart;
		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	freeTextures(&player, &gameAssets);
	Mix_FreeMusic(gameAssets.audioAssets.backgroundMusic);
	Mix_FreeChunk(gameAssets.audioAssets.pretzelSFX1);
	SDL_DestroyRenderer(gameState.renderer);
	SDL_DestroyWindow(gameState.window);
	SDL_Quit();
	return 0;
}
