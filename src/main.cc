#include <SDL2/SDL.h>
#include <iostream>


// Global Variables
SDL_Window *window;
bool isLoop = true;


void handleEventPolling() {
  SDL_Event *windowEvent;
  
  if (SDL_PollEvent(windowEvent)) {
    // Check if close button was clicked
    if (windowEvent->type == SDL_QUIT) {
      isLoop = false;
      return;
    }

    switch (windowEvent->type) {
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


int main() {
  // SDL Variables
  
  SDL_Renderer *renderer;                 // Default SDL Renderer Used
  SDL_Texture *texture;                   // Default SDL Texture that is Stretch onto entire Window (Renderer)

  // Window Data
  const char *title = "RetroPixelEngine"; // Default Window Title
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

  /* Start Looping */
  uint32_t frameCount = 0;
  uint32_t overallFrameCount = 0;
  uint32_t lastTime = SDL_GetTicks();

  while (isLoop) {
    // Measure the Speed (FPS)
    u_int32_t currentTime = SDL_GetTicks();
    frameCount++;
    if (currentTime - lastTime >= 1000) { // 1 Second Elapsed
      frameCount = 0;
      lastTime += 1000;
    }

    // Handle Event Polling
    handleEventPolling();

    // Update Title: Output FPS to Window Title
    sprintf(titleBuffer, "%s [%.2f FPS]", title, frameCount);
    SDL_SetWindowTitle(window, titleBuffer);

    // Draw Here...
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    // Keep Track of Overall FrameCount
    overallFrameCount++;
  }


  // Clean up
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
