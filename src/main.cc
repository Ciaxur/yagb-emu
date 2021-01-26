#define SDL_MAIN_HANDLED
#include "../include/imgui/imgui.h"
#include "../include/imgui/backends/imgui_impl_sdl.h"
#include "../include/imgui/backends/imgui_impl_opengl3.h"
#include "../include/imgui_club/imgui_memory_editor/imgui_memory_editor.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>            // Initialize with glewInit()
#include <iostream>
#include "../include/CPU.h"

// Global Variables
SDL_Window *window;

inline void render(ImVec4 clear_color, ImGuiIO& io) {
  ImGui::Render();
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(window);
}

inline void ImGui_NewFrame() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
  ImGui::NewFrame();
}

// TODO:
inline void drawImGui(ImGuiIO& io) {
}

void handleEventPolling(CPU *cpu) {
  SDL_Event windowEvent;
  
  while (SDL_PollEvent(&windowEvent) != 0) {
    ImGui_ImplSDL2_ProcessEvent(&windowEvent);

    // Check if close button was clicked
    if (windowEvent.type == SDL_QUIT) {
      std::cout << "Quitting...\n";
      cpu->stop();
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

  if (argc < 2) {
    perror("No ROM Path Given");
    exit(1);
  }
  // Initiate the CPU
  std::cout << "Initiating the CPU...\n";
  std::cout << "Loading ROM '" << argv[1] << "'...\n";
  CPU cpu(argv[1]);

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

  const char* glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH_pixel * RES_SCALE,
      HEIGHT_pixel * RES_SCALE,
      window_flags);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_RGB888,
      SDL_TEXTUREACCESS_STREAMING,
      WIDTH_pixel,
      HEIGHT_pixel);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync

  // Init OpenGL Loader
  bool err = glewInit() != GLEW_OK;
  if (err) {
    fprintf(stderr, "Failed to init (GLEW) OpenGL Loader!\n");
    exit(1);
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);


  /* FPS Cap */
  const int CAP_FPS = 60;
  const int TICKS_PER_FRAME = 1000 / CAP_FPS;


  /* Start Looping */
  uint32_t overallFrameCount = 0;
  uint32_t lastTime = SDL_GetTicks();
  uint32_t frameCount = 0;
  uint32_t FPS = 0;

  MemoryEditor mem_edit;


  while (cpu.isRunning()) {
    // Measure the Speed (FPS)
    uint32_t currentTime = SDL_GetTicks();
    frameCount++;
    if (currentTime - lastTime >= 1000) { // 1 Second Elapsed
      FPS = frameCount;
      frameCount = 0;
      lastTime += 1000;
    }

    // Run CPU
    cpu.nextFrame();

    // Handle Event Polling
    handleEventPolling(&cpu);

    // Update Title: Output FPS to Window Title
    sprintf(titleBuffer, "%s [%d FPS]", title, FPS);
    SDL_SetWindowTitle(window, titleBuffer);

    SDL_SetTextureColorMod(texture, 255, 0, 0);

    // Init Frame & Draw Texture
    ImGui_NewFrame();
    {
      ImGui::Begin("Emulator");
      ImGui::Text("Pointer = %p", texture);
      ImGui::Text("Size = %d x %d", WIDTH_pixel, HEIGHT_pixel);
      ImGui::Image((void*) texture, ImVec2(WIDTH_pixel, HEIGHT_pixel));
      ImGui::End();
    }

    mem_edit.DrawWindow("Memory Editor", (void*)cpu.getMemory(), 0xFFFF);

    // Draw ImGUI
    drawImGui(io);

    // Render
    render({0.45f, 0.55f, 0.60f, 1.00f}, io);

    // Keep Track of Overall FrameCount
    overallFrameCount++;

    // Frame Early Finish
    int frameTicks = SDL_GetTicks() - currentTime;
    if (frameTicks < TICKS_PER_FRAME) {
      SDL_Delay(TICKS_PER_FRAME - frameTicks);
    }
  }


  // Clean up
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
