#ifndef INIT_H
#define INIT_H

#include "common.h"
#include "structs.h"

int initPlayerStruct(struct PlayerStruct *playerStruct, int x, int y);
int initGameTextures(SDL_Renderer *renderer, SDL_Texture **playerTexture, SDL_Texture **backgroundTexture, SDL_Texture **pipe1Texture, SDL_Texture **pipe2Texture);
int initGame(struct Game *Game);
int initSubsystems(void);

void initPipeStructs(struct PipeStruct *pipe1, struct PipeStruct *pipe2);
void setPipeOffScreen(struct PipeStruct *pipe1, int x_offset);

#endif
