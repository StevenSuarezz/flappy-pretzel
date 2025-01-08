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
const float JUMP_FORCE = -8.0f;
const float FALL_MULTIPLIER = 1.75f;

struct playerStruct {
  SDL_Texture *playerTexture;
  SDL_Rect positionRect;
  float vel_y;
};

void freePlayerResources(struct playerStruct *player) {
  SDL_DestroyTexture(player->playerTexture);
}

int initPlayerStruct(struct playerStruct *player, SDL_Renderer *renderer) {
  player->positionRect.x = SCREEN_WIDTH / 3 - 50;
  player->positionRect.y = SCREEN_HEIGHT / 2 - 50;
  player->positionRect.w = 128;
  player->positionRect.h = 128;

  player->vel_y = 0.0f;

  return 0;
}

// TODO: Add pipes

// Load assets into surfaces and create textures from those surfaces
int initGameTextures(SDL_Renderer *renderer, SDL_Texture **playerTexture,
                     SDL_Texture **backgroundTexture) {
  // Player
  SDL_Surface *playerSurface = IMG_Load("./images/pretzel.png");
  if (playerSurface == NULL) {
    printf("Error loading player surface: %s\n", IMG_GetError());
    return -1;
  }

  *playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
  SDL_FreeSurface(playerSurface);

  // Background
  SDL_Surface *backgroundSurface = IMG_Load("./images/background.png");
  if (backgroundSurface == NULL) {
    printf("Error loading background surface: %s\n", IMG_GetError());
    return -1;
  }

  *backgroundTexture =
      SDL_CreateTextureFromSurface(renderer, backgroundSurface);
  SDL_FreeSurface(backgroundSurface);

  return 0;
}

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *backgroundTexture;
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

  if (initGameTextures(renderer, &player.playerTexture, &backgroundTexture) <
      0) {
    printf("Error initializing game textures\n");
    return -1;
  };

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
        case SDLK_ESCAPE:
          gameIsRunning = false;
          break;
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
    printf("DELTA TIME: %f\n", deltaTime);

    player.vel_y += GRAVITY * FALL_MULTIPLIER * deltaTime;
    player.positionRect.y += player.vel_y;

    // Render Phase
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
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
