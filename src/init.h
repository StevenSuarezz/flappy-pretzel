#ifndef INIT_H
#define INIT_H

#include "common.h"
#include "structs.h"

int initPlayerStruct(struct PlayerStruct *playerStruct);
int initGameTextures(SDL_Renderer *renderer, SDL_Texture **playerTexture, SDL_Texture **backgroundTexture, SDL_Texture **pipe1Texture, SDL_Texture **pipe2Texture);
int initGameState(struct GameState *gameState);
int initSubsystems(void);

#endif
