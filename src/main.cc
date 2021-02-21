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
struct KeyboardState {
  // Key Enabled/Disabled
  bool step_instr = false;
  bool step_frame = false;

  // Key Held down for
  int step_instr_hold = 0;
  int step_frame_hold = 0;
} keystate;

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

// TODO: Later Clean up
inline void drawImGui() {
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
      if (windowEvent.key.keysym.sym == SDL_KeyCode::SDLK_s) {
        if (keystate.step_instr_hold == 0)
          keystate.step_instr = true;
        keystate.step_instr_hold++;
      }
      if (windowEvent.key.keysym.sym == SDL_KeyCode::SDLK_m) {
        if (keystate.step_frame_hold == 0)
          keystate.step_frame = true;
        keystate.step_frame_hold++;
      }


      break;
    case SDL_KEYUP:
      // TODO: Key Press Here
      if (windowEvent.key.keysym.sym == SDL_KeyCode::SDLK_s) {
        keystate.step_instr = false;
        keystate.step_instr_hold = 0;
      }
      if (windowEvent.key.keysym.sym == SDL_KeyCode::SDLK_m) {
        keystate.step_frame = false;
        keystate.step_frame_hold = 0;
      }

      break;

    default:
      break;
    }
  }
}


int main(int argc, char *argv[]) {
  std::cout << "Starting YAGB-Emu..." << std::endl;

  if (argc < 2) {
    perror("No ROM Path Given");
    exit(1);
  }
  // Initiate the CPU
  std::cout << "Initiating the CPU...\n";
  std::cout << "Loading ROM '" << argv[1] << "'...\n";
  CPU *cpu = new CPU(argv[1]);

  // SDL Variables
  SDL_Renderer *renderer;                 // Default SDL Renderer Used
  SDL_Texture *texture;                   // Default SDL Texture that is Stretch onto entire Window (Renderer)

  // Window Data
  const char *title = "YAGB-Emu";         // Default Window Title
  char titleBuffer[256];                  // Used for Temporary Character Storage (Window Title)
  const int WIDTH_pixel = 400;
  const int HEIGHT_pixel = 400;
  const int WINDOW_WIDTH = 1600;
  const int WINDOW_HEIGHT = 1000;
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
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
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

  while (cpu->isRunning()) {
    // Measure the Speed (FPS)
    uint32_t currentTime = SDL_GetTicks();
    frameCount++;
    if (currentTime - lastTime >= 1000) { // 1 Second Elapsed
      FPS = frameCount;
      frameCount = 0;
      lastTime += 1000;
    }

    // Handle Event Polling
    handleEventPolling(cpu);

    // Update Title: Output FPS to Window Title
    sprintf(titleBuffer, "%s [%d FPS]", title, FPS);
    SDL_SetWindowTitle(window, titleBuffer);

    SDL_SetTextureColorMod(texture, 255, 0, 0);

    // Init Frame & Draw Texture
    ImGui_NewFrame();
    {
      ImGui::Begin("Emulator");
      ImGui::Text("ROM: %s", argv[1]);
      ImGui::Text("Pointer = %p", texture);
      ImGui::Text("Size = %d x %d", WIDTH_pixel, HEIGHT_pixel);
      ImGui::Image((void*) texture, ImVec2(WIDTH_pixel, HEIGHT_pixel));
      ImGui::End();
    }

    mem_edit.DrawWindow("Memory Editor", (void*)cpu->getMemory(), 0xFFFF);

    // Debug Window
    static int stepInstrCount = 1;
    {
      ImGui::Begin("Debug");

      ImGui::BeginGroup();
      if (ImGui::Button("Reset")) {
        delete cpu;
        cpu = new CPU(argv[1]);
      }
      ImGui::SameLine();
      if (ImGui::Button("Step Instruction") || keystate.step_instr || (keystate.step_instr_hold > 10)) {
        keystate.step_instr = false;
        for (int i=0; i<stepInstrCount; i++)
          cpu->tick();
      }
      ImGui::SameLine();
      if (ImGui::Button("Step Frame") || keystate.step_frame || (keystate.step_frame_hold > 10)) {
        int preFrame = cpu->getCurrentFrame();
        while (preFrame == cpu->getCurrentFrame()) {
          cpu->tick();
        }
      }
      ImGui::EndGroup();
      ImGui::InputInt("Instruction Count", &stepInstrCount);
      ImGui::Text("Calculated Frame Count: %d", cpu->totalCycles / TOTAL_INSTR_PER_FRAME);
      ImGui::Text("Frame Count: %d", cpu->getCurrentFrame());
      ImGui::Text("Instruction Count: %d", cpu->totalInstructions);
      ImGui::Text("Cycle Count: %d", cpu->totalCycles);

      for (int i=0; i < cpu->instructionStack.size(); i++) {
        if (i == cpu->instructionStack.size() - 1)
          ImGui::Text("> %s", cpu->instructionStack[i].c_str());
        else
          ImGui::Text(cpu->instructionStack[i].c_str());
      }

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // CPU State
    {
      CPU_State cpuState = cpu->getCpuStateSnapshot();
      
      ImGui::Begin("CPU State");

      // Registers
      {
        ImGui::Text("REGISTERS");
        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "A:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.A);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "B:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.B);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "C:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.C);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "D:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.D);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "E:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.E);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "F:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.F);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "H:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.H);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "L:  ");
        ImGui::SameLine();
        ImGui::Text("0x%02X", (int)cpuState.reg.L);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "HL: ");
        ImGui::SameLine();
        ImGui::Text("0x%04X", (int)((cpuState.reg.H << 8) | cpuState.reg.L));

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "SP: ");
        ImGui::SameLine();
        ImGui::Text("0x%04X", (int)cpuState.SP);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "PC: ");
        ImGui::SameLine();
        ImGui::Text("0x%04X", (int)cpuState.PC);
      }

      // Flags
      {
        ImGui::Separator();
        ImGui::Text("FLAGS");

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "Z: ");
        ImGui::SameLine();
        ImGui::Text("%d", (cpuState.reg.F & 0x80) >> 7);
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "  N: ");
        ImGui::SameLine();
        ImGui::Text("%d", (cpuState.reg.F & 0x40) >> 6);
        
        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "H: ");
        ImGui::SameLine();
        ImGui::Text("%d", (cpuState.reg.F & 0x20) >> 5);
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "  C: ");
        ImGui::SameLine();
        ImGui::Text("%d", (cpuState.reg.F & 0x10) >> 4);
      }

      // Interrupts
      {
        uint8_t IE = cpu->getMemory()[0xFFFF];
        uint8_t IF = cpu->getMemory()[0xFF0F];
        
        ImGui::Separator();
        ImGui::Text("INTERRUPTS");

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "IME: ");
        ImGui::SameLine();
        ImGui::Text("%d", cpuState.IME);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "IE [0xFFFF]:");
        ImGui::SameLine();
        ImGui::Text("0x%04X <%s>", 
          (int)IE,
          std::bitset<5>(IE).to_string().c_str()
        );

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "IF [0xFF0F]:");
        ImGui::SameLine();
        ImGui::Text("0x%04X <%s>", 
          (int)IF,
          std::bitset<5>(IF).to_string().c_str()
        );

        ImGui::Indent();

        ImGui::TextColored(ImVec4(0.102f, 0.737f, 0.612f, 1.0f), "VBLANK:");
        ImGui::SameLine();
        ImGui::Text(" IE[%d]  IF[%d]", (IE & 0x01), (IF & 0x01));
        
        ImGui::TextColored(ImVec4(0.102f, 0.737f, 0.612f, 1.0f), "STAT:  ");
        ImGui::SameLine();
        ImGui::Text(" IE[%d]  IF[%d]", (IE & 0x02) >> 1, (IF & 0x02) >> 1);

        ImGui::TextColored(ImVec4(0.102f, 0.737f, 0.612f, 1.0f), "TIMER: ");
        ImGui::SameLine();
        ImGui::Text(" IE[%d]  IF[%d]", (IE & 0x04) >> 2, (IF & 0x04) >> 2);
        
        ImGui::TextColored(ImVec4(0.102f, 0.737f, 0.612f, 1.0f), "SERIAL:");
        ImGui::SameLine();
        ImGui::Text(" IE[%d]  IF[%d]", (IE & 0x08) >> 3, (IF & 0x08) >> 3);

        ImGui::TextColored(ImVec4(0.102f, 0.737f, 0.612f, 1.0f), "JOYPAD:");
        ImGui::SameLine();
        ImGui::Text(" IE[%d]  IF[%d]", (IE & 0x10) >> 4, (IF & 0x10) >> 4);
        
        ImGui::Unindent();
      }

      // State
      {
        ImGui::Separator();
        ImGui::Text("STATE");

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "Halted: ");
        ImGui::SameLine();
        ImGui::Text("%d", cpuState.halted);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "Running: ");
        ImGui::SameLine();
        ImGui::Text("%d", cpuState.running);
      }

      // LCD
      {
        ImGui::Separator();
        ImGui::Text("LCD");

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "LY: ");
        ImGui::SameLine();
        ImGui::Text("%d", cpuState.LY);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "LY   [0xFF44]:");
        ImGui::SameLine();
        ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF44]);
        
        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "LCDC [0xFF40]:");
        ImGui::SameLine();
        ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF40]);

        ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "STAT [0xFF41]:");
        ImGui::SameLine();
        ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF41]);
      }

      ImGui::End();
    }

    // CPU Timers
    {
      ImGui::Begin("Timers");

      ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "DIV:  ");
      ImGui::SameLine();
      ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF04]);

      ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "TIMA: ");
      ImGui::SameLine();
      ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF05]);

      ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "TMA:  ");
      ImGui::SameLine();
      ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF06]);

      ImGui::TextColored(ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "TAC:  ");
      ImGui::SameLine();
      ImGui::Text("0x%04X", (int)cpu->getMemory()[0xFF07]);

      ImGui::End();
    }

    // CPU Instruction Iterations (Frequency of each instruction called)
    {
      ImGui::Begin("Instruction Frequency");

      if (ImGui::Button("Reset")) {
        cpu->instr_iters.clear();
      }

      ImGui::TextColored(ImVec4(231/255.0f, 60/255.0f, 153/255.0f, 1.0f), "FREQUENCY");
      
      for (const std::pair<uint8_t, Instr_Iterations*> &p : cpu->instr_iters) {
        ImGui::TextColored(
          ImVec4(0.9f, 0.29f, 0.235f, 1.0f), "0x%04X [%s]: ", 
          p.first, 
          p.second->opcode->getLabel().c_str()
        );
        ImGui::SameLine();
        ImGui::Text("%d", p.second->frequency);
      }
      
      ImGui::End();
    }


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
  delete cpu;
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
