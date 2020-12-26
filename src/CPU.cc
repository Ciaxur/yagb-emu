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
  
  // Initialize the Opcode & Prefix Map
  initOpcodes(this->oMap);
  initPrefixed(this->pMap);
}

/**
 * Frees up memory used
 *  - Opcode Map Pointers
 */
CPU::~CPU() {
  // Free up Mapped Opcode Execute Methods
  for (auto key: this->oMap) {
    delete key.second;
  }
  for (auto key: this->pMap) {
    delete key.second;
  }
};


// TODO:
void CPU::handleInterrupt() {}
void CPU::nextFrame() {}
void CPU::executeInstructions(int cycles) {}
