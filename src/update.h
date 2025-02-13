#ifndef UPDATE_H
#define UPDATE_H

#include "structs.h"
void update(struct Game *game, struct GameAssets *gameAssets, struct PlayerStruct *player,
			struct PipeStruct *pipe1, struct PipeStruct *pipe2, double deltaTime);

void updatePipeStructs(struct PipeStruct *pipe1, struct PipeStruct *pipe2);
bool detectCollision(struct PlayerStruct *player, struct PipeStruct *pipe1, struct PipeStruct *pipe2);
void updateScore(struct Game *game, struct PlayerStruct *player, struct PipeStruct *pipe1, struct PipeStruct *pipe2);

#endif
