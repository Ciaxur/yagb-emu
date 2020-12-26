#include "../include/CPU.h"
#include "../include/OpcodeInit.hpp"

/**
 * Initialize the CPU by constructing and populating
 *  Memory from the given ROM
 * @param ROMPath Path to the ROM
 */
CPU::CPU(std::string ROMPath): memory(ROMPath) {
  // Default Values
  cyclesLeftInCurrentFrame = TOTAL_FRAME_CYCLES;
  
  // Initialize the Opcode Map
  initOpcodes(this->opcodeMap);
}


// TODO:
void CPU::handleInterrupt() {}
void CPU::nextFrame() {}
void CPU::executeInstructions(int cycles) {}
