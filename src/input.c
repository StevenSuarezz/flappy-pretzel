#include "input.h"
#include "common.h"

void doInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameIsRunning = false;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				gameIsRunning = false;
				break;
			case SDLK_SPACE:
				player.vel_y = JUMP_FORCE;
				break;

			case SDLK_p:
				gameIsPaused = !gameIsPaused;
				// Optional: gameIsPaused ? Mix_PauseMusic() : Mix_ResumeMusic();
				break;
			}
		}
	}
}
