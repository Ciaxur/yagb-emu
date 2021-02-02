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
  this->LY = 0;
  this->currentFrame = 0;
}

/**
 * Executes the PPU based on current state of CPU
 *  and PPU
 */
void PPU::execute() {
  // Set current LY Value for CPU
  memory->write(0xFF44, this->LY);

  // Determine LCDMode based on LY State
  if (this->LY < 144) {
    if (cpu->cyclesLeft > 94) {
      this->LCDMode = 2;
    } else if (cpu->cyclesLeft > 22) {
      this->LCDMode = 3;
    } else if (cpu->cyclesLeft < 22) {
      this->LCDMode = 0;
    }
  } else {
    this->LCDMode = 1;
  }

  // Update PPU and CPU state based on both
  //  CPU's current States
  if (cpu->cyclesLeft <= 0) { // End of current scanline
    if (this->LY < 153) {
      this->LY++;
      cpu->cyclesLeft = 114;
    } else {
      this->LY = 0;
      this->currentFrame++;
      cpu->cyclesLeft = 114;
    }
  }

  // TODO: Check if left over cycles (Frequency)
  if (cpu->cyclesLeft < 0) {}

  // Execute CPU
  cpu->execute();

  // TODO: Perform PPU functions based on current LCD Mode
}
