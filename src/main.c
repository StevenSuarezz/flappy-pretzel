#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FPS 60
#define GRAVITY 9.81f

const int FRAME_DELAY = 1000 / FPS;
const float JUMP_FORCE = -5.0f;

struct playerStruct {
  SDL_Surface *playerSurface;
  SDL_Texture *playerTexture;
  SDL_Rect positionRect;
  float vel_y;
};

void freePlayerResources(struct playerStruct *player) {
  SDL_FreeSurface(player->playerSurface);
  SDL_DestroyTexture(player->playerTexture);
}

int initPlayerStruct(struct playerStruct *player, SDL_Renderer *renderer) {
  // Initialize the surface for the player character
  player->playerSurface = IMG_Load("./images/pretzel.png");
  if (player->playerSurface == NULL) {
    printf("Awww shit, here we go again: %s\n", IMG_GetError());
    return -1;
  }

  // Use that surface to create the player texture
  player->playerTexture =
      SDL_CreateTextureFromSurface(renderer, player->playerSurface);

  if (player->playerSurface == NULL) {
    printf("Aww shite, here we go again: %s\n", SDL_GetError());
    return -1;
  }

  player->positionRect.x = SCREEN_WIDTH / 3 - 50;
  player->positionRect.y = SCREEN_HEIGHT / 2 - 50;
  player->positionRect.w = 128;
  player->positionRect.h = 128;

  player->vel_y = 0.0f;

  return 0;
}

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  struct playerStruct player = {0};

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("could not initialize sdl2: %s\n", SDL_GetError());
    return -1;
  }
  window = SDL_CreateWindow("Flappy Pretzel", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("could not create window: %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Could not create renderer: %s\n", SDL_GetError());
    return -1;
  }

  if (initPlayerStruct(&player, renderer) < 0) {
    printf("Error initializing player struct\n");
    return -1;
  }

  Uint64 lastTime = SDL_GetTicks64();
  Uint64 frameStart;
  int frameTime;

  SDL_Event event;
  bool gameIsRunning = true;

  // Main game loop
  while (gameIsRunning) {
    // Input Phase
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameIsRunning = false;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          player.vel_y = JUMP_FORCE;
          break;
        }
      }
    }

    // Update Phase
    frameStart = SDL_GetTicks64();
    double deltaTime = (frameStart - lastTime) / 1000.0f;
    lastTime = frameStart;

    player.vel_y += GRAVITY * deltaTime;
    player.positionRect.y += player.vel_y;

    // Render Phase
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, player.playerTexture, NULL, &player.positionRect);
    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks64() - frameStart;
    if (frameTime < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }

  freePlayerResources(&player);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
