#include "update.h"
#include "util.h"

void update(struct GameState *gameState, struct GameAssets *gameAssets, struct PlayerStruct *player,
			struct PipeStruct *pipe1, struct PipeStruct *pipe2, double deltaTime) {
	if (!gameState->isPaused) {
		if (detectCollision(player, pipe1, pipe2) && Mix_Playing(0) == 0) {
			Mix_PlayChannel(0, gameAssets->audioAssets.pretzelSFX1, 0);
		}
		// Update player
		player->vel_y += GRAVITY * FALL_MULTIPLIER * deltaTime;
		printf("Player velocity: %f\n", player->vel_y);
		player->positionRect.y += player->vel_y;
		player->angle = player->vel_y * PLAYER_ANGLE_MULTIPLIER;

		// Update pipes
		updatePipeStructs(pipe1, pipe2);
	}
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
