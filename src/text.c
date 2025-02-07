#include "text.h"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>

int initScoreText(SDL_Renderer *renderer, struct ScoreText *scoreText) {
	setScoreText(renderer, scoreText, 0);
	scoreText->scorePositionRect.x = 0;
	scoreText->scorePositionRect.y = 0;
	scoreText->scorePositionRect.w = 100;
	scoreText->scorePositionRect.h = 100;

	// TODO: Implement return proper return values for error handling
	return 0;
}

void setScoreText(SDL_Renderer *renderer, struct ScoreText *scoreText, uint score) {
	if (scoreText->scoreTexture) {
		SDL_DestroyTexture(scoreText->scoreTexture);
	}

	TTF_Font *soriaFont = TTF_OpenFont("../assets/font/soria-font.ttf", 24);

	snprintf(scoreString, sizeof(scoreString), "Score: %d", score);
	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(soriaFont, scoreString, colorWhite);
	scoreText->scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(soriaFont);
}
