#include "draw.h"
#include "common.h"

void render(struct GameState *gameState, struct GameAssets *gameAssets, struct PlayerStruct *player,
			struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	SDL_SetRenderDrawColor(gameState->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gameState->renderer);
	SDL_RenderCopy(gameState->renderer, gameAssets->backgroundTexture, NULL, NULL);

	// Render player
	SDL_RenderCopyEx(gameState->renderer, player->playerTexture, NULL, &player->positionRect, player->angle, NULL, SDL_FLIP_NONE);

	// Render pipes
	SDL_RenderCopyEx(gameState->renderer, pipe1->pipeTexture, NULL, &pipe1->topPositionRect, 0.0f, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderCopy(gameState->renderer, pipe1->pipeTexture, NULL, &pipe1->bottomPositionRect);

	SDL_RenderCopyEx(gameState->renderer, pipe2->pipeTexture, NULL, &pipe2->topPositionRect, 0.0f, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderCopy(gameState->renderer, pipe2->pipeTexture, NULL, &pipe2->bottomPositionRect);

	drawDebugRects(gameState->renderer, player, pipe1, pipe2);

	SDL_RenderPresent(gameState->renderer);
}

void drawDebugRects(SDL_Renderer *renderer, struct PlayerStruct *player, struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	SDL_RenderDrawRect(renderer, &player->positionRect);
	SDL_RenderDrawRect(renderer, &pipe1->topPositionRect);
	SDL_RenderDrawRect(renderer, &pipe1->bottomPositionRect);
	SDL_RenderDrawRect(renderer, &pipe2->topPositionRect);
	SDL_RenderDrawRect(renderer, &pipe2->bottomPositionRect);
}
