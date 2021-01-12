#include "../include/PPU.h"

/**
 * Initializes the PPU, sharing the Memory between
 *  the CPU & PPU
 * @param cpu Pointer to the CPU for Communications
 * @param memory Pointer to Memory shared between the PPU & CPU
 */
PPU::PPU(CPU *cpu, Memory *memory) {
  this->cpu = cpu;
  this->memory = memory;
}

/**
 * Generates Scanline with respect to LY and Mode
 * @param LY Current Horizontal Scanline
 */
void PPU::generateScanline(int LY) {
  if (LY < 144) {
    // Mode 2
    this->LCDMode = 2;
    cpu->executeInstructions(20);

    // Mode 3
    this->LCDMode = 3;
    cpu->executeInstructions(72);

    // Mode 0
    this->LCDMode = 0;
    cpu->executeInstructions(22);
  } else {
    // Mode 1
    this->LCDMode = 1;
    cpu->executeInstructions(114);
  }
}
