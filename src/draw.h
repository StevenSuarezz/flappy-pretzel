#ifndef DRAW_H
#define DRAW_H

#include "structs.h"

void render(struct GameState *gameState, struct GameAssets *gameAssets, struct PlayerStruct *player,
			struct PipeStruct *pipe1, struct PipeStruct *pipe2);

void drawDebugRects(SDL_Renderer *renderer, struct PlayerStruct *player,
					struct PipeStruct *pipe1, struct PipeStruct *pipe2);

#endif
