#include "draw.h"
#include "common.h"

void render(struct Game *game, struct GameAssets *gameAssets, struct PlayerStruct *player,
			struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(game->renderer);
	SDL_RenderCopy(game->renderer, gameAssets->backgroundTexture, NULL, NULL);

	// Render player
	SDL_RenderCopyEx(game->renderer, player->playerTexture, NULL, &player->textureRect, player->angle, NULL, SDL_FLIP_NONE);

	// Render pipes
	SDL_RenderCopyEx(game->renderer, pipe1->pipeTexture, NULL, &pipe1->topPositionRect, 0.0f, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderCopy(game->renderer, pipe1->pipeTexture, NULL, &pipe1->bottomPositionRect);

	SDL_RenderCopyEx(game->renderer, pipe2->pipeTexture, NULL, &pipe2->topPositionRect, 0.0f, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderCopy(game->renderer, pipe2->pipeTexture, NULL, &pipe2->bottomPositionRect);

	drawDebugRects(game->renderer, player, pipe1, pipe2);

	SDL_RenderPresent(game->renderer);
}

void drawDebugRects(SDL_Renderer *renderer, struct PlayerStruct *player, struct PipeStruct *pipe1, struct PipeStruct *pipe2) {
	// Render texture rect in white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &player->textureRect);

	// Render player and pipe hitbox rects in red
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &player->collisionRect);
	SDL_RenderDrawRect(renderer, &pipe1->topPositionRect);
	SDL_RenderDrawRect(renderer, &pipe1->bottomPositionRect);
	SDL_RenderDrawRect(renderer, &pipe2->topPositionRect);
	SDL_RenderDrawRect(renderer, &pipe2->bottomPositionRect);
}
