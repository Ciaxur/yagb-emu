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
  this->initOpcodes(this);
  this->initPrefixed(this);
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


/**
 * Sets Half-Carry flag if a half carry occured
 * @param prev The previous value
 * @param after Result of the previous value
 * @return Result of the Set (if needed)
 */
void CPU::checkHalfCarry(uint8_t prev, uint8_t after) {
  this->reg.F &= 0xFD;                    // Unset H Flag
  if ((prev & 0x0F) != (after & 0x0F))    // LSB Change
    if ((prev & 0xF0) != (after & 0xF0))  // MSB Change
      this->reg.F |= 0x02;                // Set H Flag
}

/**
 * Sets Carry flag if a carry occured
 * @param prev The previous value
 * @param after Result of the previous value
 * @return Result of the Set (if needed)
 */
void CPU::checkCarry(uint16_t prev, uint16_t after) {
  this->reg.F &= 0xFE;                        // Unset C Flag
  if ((prev & 0xFF) != (after & 0xFF))        // LSB Change
    if ((prev & 0xFF00) != (after & 0xFF00))  // MSB Change
      this->reg.F |= 0x01;                    // Set C Flag
}



// TODO:
void CPU::handleInterrupt() {}
void CPU::nextFrame() {}
void CPU::executeInstructions(int cycles) {}
