#include "input.h"
#include "common.h"

void doInput(struct GameState *gameState, struct PlayerStruct *playerStruct) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameState->gameIsRunning = false;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				gameState->gameIsRunning = false;
				break;
			case SDLK_SPACE:
				playerStruct->vel_y = JUMP_FORCE;
				break;

			case SDLK_p:
				gameState->gameIsPaused = !gameState->gameIsPaused;
				// Optional: gameIsPaused ? Mix_PauseMusic() : Mix_ResumeMusic();
				break;
			}
		}
	}
}
