#include "../include/CPU.h"

/* 8-bit Arithmetic and Logic Instructions */
void CPU::ADC(uint8_t *r8) {        // ADC A, r8
  this->ADC(*r8);
}

void CPU::ADC(uint16_t a16) {       // ADC A, [HL]
  this->ADC(this->memory.read(a16));
}

void CPU::ADC(uint8_t u8) {         // ADC A, u8
  uint8_t result = this->reg.A + (this->reg.F & 0x01) + u8;

  // Set Flags
  if (result == 0)    // Zero Flag
    this->reg.F |= 0x80;
  this->reg.F &= 0x7F; // Unset N Flag
  this->checkHalfCarry(result, this->reg.A);
  this->checkCarry(result, this->reg.A);

  // Set new A Value
  this->reg.A = result;
}

void CPU::ADD(uint8_t *r8) {        // ADD A, r8
  this->ADD(*r8);
}

void CPU::ADD(uint16_t a16) {       // ADD A, [HL]
  this->ADD(this->memory.read((a16)));
}

void CPU::ADD(uint8_t u8) {         // ADD A, u8
  uint8_t result = this->reg.A + u8;

  // Set Flags
  if (result == 0)    // Zero Flag
    this->reg.F |= 0x80;
  this->reg.F &= 0x7F; // Unset N Flag
  this->checkHalfCarry(result, this->reg.A);
  this->checkCarry(result, this->reg.A);

  // New A Value
  this->reg.A = result;
}

void CPU::AND(uint8_t *r8) {        // AND A, r8
  this->AND(*r8);
}

void CPU::AND(uint16_t a16) {       // AND A, [HL]
  this->AND(this->memory.read(a16));
}

void CPU::AND(uint8_t u8) {         // AND A, u8
  uint8_t result = this->reg.A & u8;

  // Set Flags
  if (result == 0)    // Zero Flag
    this->reg.F |= 0x80;
  this->reg.F &= 0x7F;  // Unset N Flag
  this->reg.F |= 0x02;  // Set H Flag
  this->reg.F &= 0xFE;  // Unset C Flag

  // New A Value
  this->reg.A = result;
}
