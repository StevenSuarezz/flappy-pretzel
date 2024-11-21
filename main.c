#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <stdio.h>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
}
