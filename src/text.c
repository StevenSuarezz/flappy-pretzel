#include "text.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>

int initText(SDL_Renderer *renderer, struct ScoreText *scoreText) {
	TTF_Font *soriaFont = TTF_OpenFont("../assets/font/soria-font.ttf", 24);

	snprintf(scoreString, sizeof(scoreString), "Score: 0");

	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(soriaFont, scoreString, colorWhite);
	scoreText->scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	scoreText->scorePositionRect.x = 0;
	scoreText->scorePositionRect.y = 0;
	scoreText->scorePositionRect.w = 100;
	scoreText->scorePositionRect.h = 100;

	// TODO: Implement return proper return values for error handling
	return 0;
}
