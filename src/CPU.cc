#include "../include/CPU.h"
#include "../include/OpcodeInit.hpp"
#include "../include/PPU.h"

/**
 * Initialize the CPU by constructing and populating
 *  Memory from the given ROM
 * @param ROMPath Path to the ROM
 */
CPU::CPU(std::string ROMPath): memory(ROMPath) {
  // Default Values
  lineCycles = TOTAL_LINE_CYCLES;
  extraCycles = 0;
  halted = false;

  // Initialize the Opcode & Prefix Map
  this->initOpcodes(this);
  this->initPrefixed(this);

  ppu = new PPU(this, &this->memory);
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
  delete this->ppu;
};

/**
 * Sets the Z Flag (Bit 7) to given State
 * @param state State of the Flag
 */
void CPU::setZeroFlag(bool state) {
  state ? this->reg.F |= 0x80 : this->reg.F &= 0x7F;
}

/**
 * Sets the N Flag (Bit 6) to given State
 * @param state State of the Flag
 */
void CPU::setAddSubFlag(bool state) {
  state ? this->reg.F |= 0x40 : this->reg.F &= 0xBF;
}

/**
 * Sets the H Flag (Bit 5) to given State
 * @param state State of the Flag
 */
void CPU::setHalfCarryFlag(bool state) {
  state ? this->reg.F |= 0x20 : this->reg.F &= 0xDF;
}

/**
 * Sets the C Flag (Bit 4) to given State
 * @param state State of the Flag
 */
void CPU::setCarryFlag(bool state) {
  state ? this->reg.F |= 0x10 : this->reg.F &= 0xEF;
}

/**
 * Sets Half-Carry flag if a half carry occurred for 8bit Value
 * @param prev The previous value
 * @param after Result of the previous value
 * @return Result of the Set (if needed)
 */
void CPU::checkHalfCarry(uint8_t prev, uint8_t after) { // Overflow from 3rd Bit
  this->reg.F &= 0xDF;                    // Unset H Flag
  if ((prev & 0x0F) != (after & 0x0F))    // LSB Change
    if ((prev & 0xF0) != (after & 0xF0))  // MSB Change
      this->reg.F |= 0x20;                // Set H Flag
}

/**
 * Sets Carry flag if a carry occurred for 8bit Value
 * @param prev The previous value
 * @param after Result of the previous value
 * @return Result of the Set (if needed)
 */
void CPU::checkCarry(uint8_t prev, uint16_t after) { // Overflow from 7th Bit
  this->reg.F &= 0xEF;                        // Unset C Flag
  if ((prev & 0xFF) != (after & 0xFF))        // LSB Change
    if ((prev & 0xFF00) != (after & 0xFF00))  // MSB Change
      this->reg.F |= 0x10;                    // Set C Flag
}


/**
 * Main Run Function for the CPU
 *  - Executes Instructions
 *  - Communications between PPU & Memory
 */
void CPU::nextFrame() {
  lineCycles = TOTAL_LINE_CYCLES;

  // Prompt PPU to Generate Scanline
  for (int LY = 0; LY <= 153; LY++) {
    ppu->generateScanline(LY);
  }
}

/**
 * Handle CPU Instructions from PC! 🤠🤠🤠🤠
 * @param cycles Cycles the CPU is allowed to Run for
 */
void CPU::executeInstructions(int cycles) {
  int cyclesLeft = cycles;
  handleInterrupt();

  while (cyclesLeft > 0) {
    // Get Opcode Value
    uint8_t currentOpcode = this->memory.read(this->PC);

    // Condition between Opcode & PREFIX Table
    Opcode *opcodeObj;
    if (currentOpcode!= 0xCB) {
      opcodeObj = oMap[currentOpcode];
    } else {
      opcodeObj = pMap[currentOpcode + 1];
    }

    // Exec Opcode
    opcodeObj->exec();

    // Decrement CyclesLeft & Additional Cycles taken by Opcode
    cyclesLeft -= this->extraCycles + opcodeObj->machineCycles;
    this->extraCycles = 0;

    // Set new PC
    this->PC += opcodeObj->length;
  }
}


// TODO:
void CPU::handleInterrupt() {}

