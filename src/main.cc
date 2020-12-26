#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iostream>
#include "../include/CPU.h"

// Global Variables
SDL_Window *window;
bool isLoop = true;


void handleEventPolling() {
  SDL_Event windowEvent;
  
  while (SDL_PollEvent(&windowEvent) != 0) {
    // Check if close button was clicked
    if (windowEvent.type == SDL_QUIT) {
      isLoop = false;
      return;
    }

    switch (windowEvent.type) {
    // Handle Key Presses
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      // TODO: Key Press Here
      break;

    default:
      break;
    }
  }
}


int main(int argc, char **argv) {
  std::cout << "Starting YAGB-Emu..." << std::endl;

  // Initiate the CPU
  std::cout << "Initiating the CPU...\n";
  CPU cpu("misc/drmario.gb");

  // SDL Variables
  SDL_Renderer *renderer;                 // Default SDL Renderer Used
  SDL_Texture *texture;                   // Default SDL Texture that is Stretch onto entire Window (Renderer)

  // Window Data
  const char *title = "YAGB-Emu";         // Default Window Title
  char titleBuffer[256];                  // Used for Temporary Character Storage (Window Title)
  const int WIDTH_pixel = 400;
  const int HEIGHT_pixel = 400;
  const int RES_SCALE = 1;

  /* Configure SDL Properties */
  // Initialize Window, Renderer, & Texture
  //  Texture will be used to draw on
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH_pixel * RES_SCALE,
      HEIGHT_pixel * RES_SCALE,
      SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_RGB888,
      SDL_TEXTUREACCESS_STREAMING,
      WIDTH_pixel,
      HEIGHT_pixel);

  /* FPS Cap */
  const int CAP_FPS = 60;
  const int TICKS_PER_FRAME = 1000 / CAP_FPS;


  /* Start Looping */
  uint32_t overallFrameCount = 0;
  uint32_t lastTime = SDL_GetTicks();
  uint32_t frameCount = 0;
  uint32_t FPS = 0;

  while (isLoop) {
    // Measure the Speed (FPS)
    uint32_t currentTime = SDL_GetTicks();
    frameCount++;
    if (currentTime - lastTime >= 1000) {   // 1 Second Elapsed
      FPS = frameCount;
      frameCount = 0;
      lastTime += 1000;
    }

    // Run CPU
    cpu.nextFrame();

    // Handle Event Polling
    handleEventPolling();

    // Update Title: Output FPS to Window Title
    sprintf(titleBuffer, "%s [%d FPS]", title, FPS);
    SDL_SetWindowTitle(window, titleBuffer);

    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Draw Here...
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    // Keep Track of Overall FrameCount
    overallFrameCount++;

    // Frame Early Finish
    int frameTicks = SDL_GetTicks() - currentTime;
    if (frameTicks < TICKS_PER_FRAME) {
      SDL_Delay(TICKS_PER_FRAME - frameTicks);
    }
  }


  // Clean up
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
