#ifndef TEXT_H
#define TEXT_H

#include "structs.h"

static const SDL_Color colorWhite = {255, 255, 255};

static char scoreString[32];
int initScoreText(SDL_Renderer *renderer, struct ScoreText *scoreText);
void setScoreText(SDL_Renderer *renderer, struct ScoreText *scoreText, uint score);

#endif
