#include "../include/CPU.h"

/* 8-bit Arithmetic and Logic Instructions */
void CPU::ADC(uint8_t *r8) {                // ADC A, r8
  this->ADC(*r8);
}

void CPU::ADC(uint16_t a16) {               // ADC A, [HL]
  this->ADC(this->memory.read(a16));
}

void CPU::ADC(uint8_t u8) {                 // ADC A, u8
  uint8_t result = this->reg.A + (this->reg.F & 0x10) + u8;

  // Set Flags
  if (result == 0)                    // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(false);   // Unset N Flag
  this->checkHalfCarry(result, this->reg.A);
  this->checkCarry(result, this->reg.A);

  // Set new A Value
  this->reg.A = result;
}

void CPU::ADD(uint8_t *r8) {                // ADD A, r8
  this->ADD(*r8);
}

void CPU::ADD(uint16_t a16) {               // ADD A, [HL]
  this->ADD(this->memory.read((a16)));
}

void CPU::ADD(uint8_t u8) {                 // ADD A, u8
  uint8_t result = this->reg.A + u8;

  // Set Flags
  if (result == 0)                    // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(false);   // Unset N Flag
  this->checkHalfCarry(result, this->reg.A);
  this->checkCarry(result, this->reg.A);

  // New A Value
  this->reg.A = result;
}

void CPU::AND(uint8_t *r8) {                // AND A, r8
  this->AND(*r8);
}

void CPU::AND(uint16_t a16) {               // AND A, [HL]
  this->AND(this->memory.read(a16));
}

void CPU::AND(uint8_t u8) {                 // AND A, u8
  uint8_t result = this->reg.A & u8;

  // Set Flags
  if (result == 0)                    // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(false);   // Unset N Flag
  this->setHalfCarryFlag(true); // Set H Flag
  this->setCarryFlag(false);    // Unset C Flag

  // New A Value
  this->reg.A = result;
}

void CPU::CP(uint8_t *r8) {                 // CP A, r8
  this->CP(*r8);
}

void CPU::CP(uint16_t a16) {                // CP A, [HL]
  this->CP(this->memory.read(a16));
}

void CPU::CP(uint8_t u8) {                  // CP A, u8
  uint8_t result = this->reg.A - u8;

  // Set Flags
  if (result == 0)                  // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->reg.A, result); // Set if borrow from bit 4
  this->checkCarry(this->reg.A, result); // Set if borrow
}

void CPU::DEC(uint8_t *r8) {                // DEC r8
  uint8_t result = *r8 - 1;

  // Set Flags
  if (result == 0)                   // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(*r8, result); // Set if borrow from bit 4

  // New r8 value
  *r8 = result;
}

void CPU::DEC(uint16_t a16) {               // DEC [HL]
  uint8_t result = this->memory.read(a16) - 1;

  // Set Flags
  if (result == 0)                  // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->memory.read(a16), result); // Set if borrow from bit 4

  this->memory.write(a16, result);
}

void CPU::INC(uint8_t *r8) {                // INC r8
  uint8_t result = *r8 + 1;

  // Set Flags
  if (result == 0)                    // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(false);  // Unset N Flag
  this->checkHalfCarry(*r8, result); // Set if overflow from bit 3

  // New r8 value
  *r8 = result;
}

void CPU::INC(uint16_t a16) {               // INC [HL]
  uint8_t result = this->memory.read(a16) + 1;

  // Set Flags
  if (result == 0)                   // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(false);  // Unset N Flag
  this->checkHalfCarry(this->memory.read(a16), result); // Set if overflow from bit 3

  this->memory.write(a16, result);
}

void CPU::OR(uint8_t *r8) {                 // OR A, r8
  this->OR(*r8);
}

void CPU::OR(uint16_t a16) {                // OR A, [HL]
  this->OR(this->memory.read(a16));
}

void CPU::OR(uint8_t u8) {                  // OR A, u8
  uint8_t result = this->reg.A | u8;

  // Set Flags
  this->reg.F = 0x00;                // Reset Flags
  if (result == 0)                   // Zero Flag
    this->setZeroFlag(true);

  this->reg.A = result;
}

void CPU::SBC(uint8_t *r8) {                // SBC A, r8
  this->SBC(*r8);
}

void CPU::SBC(uint16_t a16) {               // SBC A, [HL]
  this->SBC(this->memory.read(a16));
}

void CPU::SBC(uint8_t u8) {                 // SBC A, u8
  uint8_t result = this->reg.A - u8 - (this->reg.F & 0x10);

  // Set Flags
  if (result == 0)                   // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->reg.A, result);
  this->checkCarry(this->reg.A, result);

  this->reg.A = result;
}

void CPU::SUB(uint8_t *r8) {                // SUB A, r8
  this->SUB(*r8);
}

void CPU::SUB(uint16_t a16) {               // SUB A, [HL]
  this->SUB(this->memory.read(a16));
}

void CPU::SUB(uint8_t u8) {                 // SUB A, u8
  uint8_t result = this->reg.A - u8;

  // Set Flags
  if (result == 0)                   // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->reg.A, result);
  this->checkCarry(this->reg.A, result);

  this->reg.A = result;
}

void CPU::XOR(uint8_t *r8) {                // XOR A, r8
  this->XOR(*r8);
}

void CPU::XOR(uint16_t a16) {               // XOR A, [HL]
  this->XOR(this->memory.read(a16));
}

void CPU::XOR(uint8_t u8) {                 // XOR A, u8
  uint8_t result = this->reg.A ^ u8;

  // Set Flags
  this->reg.F = 0x00;                // Reset Flags
  if (result == 0)                   // Zero Flag
    this->setZeroFlag(true);

  this->reg.A = result;
}

/* 16-bit Arithmetic Instructions */

void CPU::ADD_HL(uint16_t r16) {             // ADD HL, r16
  uint16_t HL = (this->reg.H << 8) | this->reg.L;
  uint16_t result = HL + r16;

  // Set Flags
  this->setAddSubFlag(false);  // Unset N Flag
  this->checkHalfCarry(HL >> 8, result >> 8);
  this->checkCarry(HL >> 8, result >> 8);

  this->reg.H = result >> 8;
  this->reg.L = result & 0xFF;
}

void CPU::DEC(uint8_t *r1, uint8_t *r2) {    // DEC r16
  uint16_t r16 = (*r1 << 8) | *r2;
  uint16_t result = r16--;

  *r1 = result >> 8;
  *r2 = result & 0xFF;
}

void CPU::INC(uint8_t *r1, uint8_t *r2) {    // INC r16
  uint16_t r16 = (*r1 << 8) | *r2;
  uint16_t result = r16++;

  *r1 = result >> 8;
  *r2 = result & 0xFF;
}
