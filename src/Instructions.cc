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

void CPU::ADDHL(uint16_t r16) {             // ADD HL, r16
  uint16_t HL = (this->reg.H << 8) | this->reg.L;
  uint16_t result = HL + r16;

  // Set Flags
  this->setAddSubFlag(false);  // Unset N Flag
  this->checkHalfCarry(HL >> 8, result >> 8);
  this->checkCarry(HL >> 8, result >> 8);

  this->reg.H = result >> 8;
  this->reg.L = result & 0xFF;
}

void CPU::DEC(uint8_t *ru, uint8_t *rl) {    // DEC r16
  uint16_t r16 = (*ru << 8) | *rl;
  uint16_t result = r16--;

  *ru = result >> 8;
  *rl = result & 0xFF;
}

void CPU::INC(uint8_t *ru, uint8_t *rl) {    // INC r16
  uint16_t r16 = (*ru << 8) | *rl;
  uint16_t result = r16++;

  *ru = result >> 8;
  *rl = result & 0xFF;
}

/* Bit Operations Instructions */

void CPU::BIT(uint8_t u3, uint8_t *r8) {     // BIT u3, r8
  // Check bit at u3 in r8's Bytes
  // Shift byte to u3 Bit to check if R8 Bit is set
  if ( ((1 << u3) & *r8) == 0 ) {
    this->setZeroFlag(true);
  }
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(true);
}

void CPU::BIT(uint8_t u3, uint16_t a16) {    // BIT u3, [HL]
  uint8_t value = this->memory.read(a16);
  this->BIT(u3, &value);
  this->memory.write(a16, value);
}

void CPU::RES(uint8_t u3, uint8_t *r8) {     // RES u3, r8
  // CLEAR bit at u3 in r8's Bytes
  // Shift byte to u3 Bit
  *r8 = ~(1 << u3) & *r8;
}

void CPU::RES(uint8_t u3, uint16_t a16) {    // RES u3, [HL]
  uint8_t value = this->memory.read(a16);
  this->RES(u3, &value);
  this->memory.write(a16, value);
}

void CPU::SET(uint8_t u3, uint8_t *r8) {    // SET u3, r8
  *r8 = (1 << u3) | *r8;
}

void CPU::SET(uint8_t u3, uint16_t a16) {   // SET u3, [HL]
  uint8_t value = this->memory.read(a16);
  this->SET(u3, &value);
  this->memory.write(a16, value);
}

void CPU::SWAP(uint8_t *r8) {               // SWAP r8
  uint8_t L = *r8 >> 4;
  uint8_t R = *r8 << 4;
  uint8_t result = L | R;

  // Set Flags
  if (result == 0)                     // Zero Flag
    this->setZeroFlag(true);
  this->setAddSubFlag(false);     // Unset N Flag
  this->setHalfCarryFlag(false);  // Unset Half Carry Flag
  this->setCarryFlag(false);      // Unset Carry Flag
}

void CPU::SWAP(uint16_t a16) {             // SWAP [HL]
  uint8_t value = this->memory.read(a16);
  this->SWAP(&value);
  this->memory.write(a16, value);
}

/* Bit Shift Instructions */

void CPU::RL(uint8_t *r8) {                // RL r8
  uint8_t carry = this->reg.F & 0x01;

  // Set Carry flag according to 7th Bit
  this->setCarryFlag((*r8 & 0x80) != 0);

  *r8 = (*r8 << 1) | carry;  // Set right most bit

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::RL(uint16_t a16) {               // RL [HL]
  uint8_t value = this->memory.read(a16);
  this->RL(&value);
  this->memory.write(a16, value);
}

void CPU::RLA() {                          // RLA
  this->RL(&this->reg.A);
  this->setZeroFlag(false);
}

void CPU::RLC(uint8_t *r8) {               // RLC r8
  // Set Carry flag according to 7th Bit
  this->setCarryFlag((*r8 & 0x80) != 0);

  // Carry 7th Bit over
  *r8 = (*r8 << 1) | (this->reg.F & 0x01);

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::RLC(uint16_t a16) {              // RLC [HL]
  uint8_t value = this->memory.read(a16);
  this->RLC(&value);
  this->memory.write(a16, value);
}

void CPU::RLCA() {                         // RLCA
  this->RLC(&this->reg.A);
  this->setZeroFlag(false);
}

void CPU::RR(uint8_t *r8) {                // RR r8
  uint8_t carry = this->reg.F & 0x01;

  // Set Carry flag according to 7th Bit
  this->setCarryFlag((*r8 & 0x01) != 0);

  *r8 = (*r8 >> 1) | carry;  // Set left most bit

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::RR(uint16_t a16) {               // RR [HL]
  uint8_t value = this->memory.read(a16);
  this->RR(&value);
  this->memory.write(a16, value);
}

void CPU::RRA() {                          // RRA
  this->RL(&this->reg.A);
  this->setZeroFlag(false);
}

void CPU::RRC(uint8_t *r8) {                // RRC r8
  // Set Carry flag according to 7th Bit
  this->setCarryFlag((*r8 & 0x01) != 0);

  // Carry 7th Bit over
  *r8 = (*r8 >> 1) | (this->reg.F & 0x01);

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::RRC(uint16_t a16) {              // RRC [HL]
  uint8_t value = this->memory.read(a16);
  this->RRC(&value);
  this->memory.write(a16, value);
}

void CPU::RRCA() {                         // RRCA
  this->RRC(&this->reg.A);
  this->setZeroFlag(false);
}

void CPU::SLA(uint8_t *r8) {               // SLA r8
  // Set Carry from Left Shift
  this->setCarryFlag((*r8 & 0x80) != 0);

  // Shift Left
  *r8 = *r8 << 1;

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::SLA(uint16_t a16) {              // SLA [HL]
  uint8_t value = this->memory.read(a16);
  this->SLA(&value);
  this->memory.write(a16, value);
}

void CPU::SRA(uint8_t *r8) {               // SRA r8
  // Set Carry from Right Shift
  this->setCarryFlag((*r8 & 0x01) != 0);

  // Shift Arithmetic Right
  uint8_t topBit = *r8 & 0x80;
  *r8 = topBit | (*r8 >> 1);

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::SRA(uint16_t a16) {              // SRA [HL]
  uint8_t value = this->memory.read(a16);
  this->SRA(&value);
  this->memory.write(a16, value);
}

void CPU::SRL(uint8_t *r8) {                // SRL r8
  // Set Carry from Right Shift
  this->setCarryFlag((*r8 & 0x01) != 0);

  // Shift Logic Right
  *r8 = *r8 >> 1;

  // Set Flags
  if (*r8 == 0)
    this->setZeroFlag(true);
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
}

void CPU::SRL(uint16_t a16) {               // SRL [HL]
  uint8_t value = this->memory.read(a16);
  this->SRL(&value);
  this->memory.write(a16, value);
}

/* Load Instructions */

void CPU::LD(uint8_t *r1, uint8_t *r2) {    // LD r8, r8
  *r1 = *r2;
}

void CPU::LD(uint8_t *r8, uint8_t u8) {     // LD r8, u8
  *r8 = u8;
}

void CPU::LD(uint8_t *ru, uint8_t *rl, uint16_t u16) { // LD r16, u16
  *ru = u16 >> 8;
  *rl = u16 & 0xFF;
}

void CPU::LD(uint16_t a16, uint8_t *r8) {   // LD [HL], r8
  this->memory.write(a16, *r8);
}

void CPU::LD(uint16_t a16, uint8_t u8) {     // LD [HL], u8
  this->memory.write(a16, u8);
}

void CPU::LD(uint8_t *r8, uint16_t a16) {   // LD r8, [HL]
  *r8 = this->memory.read(a16);
}

void CPU::LD(uint16_t a16) {                // LD [r16], A | LD [u16], A
  this->memory.write(a16, this->reg.A);
}

void CPU::LDH(uint16_t a16) {               // LDH [n16], A
  if (a16 >= 0xFF00 && a16 <= 0xFFFF) {
    this->memory.write(a16, this->reg.A);
  }
}

void CPU::LDHCA() {                          // LDH [C], A
  this->memory.write(0xFF00 + this->reg.C, this->reg.A);
}

void CPU::LDA(uint16_t a16) {               // LD A, [r16] | LD A, [u16]
  this->reg.A = this->memory.read(a16);
}

void CPU::LDHA(uint16_t a16) {              // LD A, [n16]
  if (a16 >= 0xFF00 && a16 <= 0xFFFF) {
    this->reg.A = this->memory.read(a16);
  }
}

void CPU::LDHAC() {                         // LDH A, [C]
  this->reg.A = this->memory.read(0xFF00 + this->reg.C);
}

void CPU::LDHLI() {            // LD [HLI], A
  uint16_t HL = (this->reg.H << 8) | this->reg.L;

  this->memory.write(HL, this->reg.A);
  HL++;

  this->reg.H = HL >> 8;
  this->reg.L = HL & 0xFF;
}

void CPU::LDHLD() {                         // LD [HLD], A
  uint16_t HL = (this->reg.H << 8) | this->reg.L;

  this->memory.write(HL, this->reg.A);
  HL--;

  this->reg.H = HL >> 8;
  this->reg.L = HL & 0xFF;
}

void CPU::LDAHLI() {                        // LD A, [HLI]
  uint16_t HL = (this->reg.H << 8) | this->reg.L;

  this->reg.A = this->memory.read(HL);
  HL++;

  this->reg.H = HL >> 8;
  this->reg.L = HL & 0xFF;
}

void CPU::LDAHLD() {                        // LD A, [HLD]
  uint16_t HL = (this->reg.H << 8) | this->reg.L;

  this->reg.A = this->memory.read(HL);
  HL--;

  this->reg.H = HL >> 8;
  this->reg.L = HL & 0xFF;
}

/* Jumps and Subroutines */

void CPU::CALL(uint16_t u16) {                  // CALL, u16
  // Push Address to Stack
  this->PUSH(&this->PC);

  // JP to address
  this->PC = u16;
}

void CPU::CALL(ConditionCode cc, uint16_t a16) {   // CALL cc, u16
  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        this->CALL(a16);
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        this->CALL(a16);
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        this->CALL(a16);
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        this->CALL(a16);
      break;
  }
}

void CPU::JP(uint16_t a16) {                    // JP HL | JP u16
  this->PC = a16;
}

void CPU::JP(ConditionCode cc, uint16_t a16) {  // JP cc, u16
  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        this->JP(a16);
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        this->JP(a16);
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        this->JP(a16);
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        this->JP(a16);
      break;
  }
}

void CPU::JR(int8_t e8) {                       // JR e8
  this->PC = static_cast<uint16_t>(e8 + this->PC);
}

void CPU::JR(ConditionCode cc, int8_t e8) {     // JR cc, e8
  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        this->JR(e8);
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        this->JR(e8);
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        this->JR(e8);
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        this->JR(e8);
      break;
  }
}

void CPU::RET(ConditionCode cc) {                 // RET cc
  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        this->RET();
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        this->RET();
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        this->RET();
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        this->RET();
      break;
  }
}

void CPU::RET() {                                // RET
  this->POP(&this->PC);
}

void CPU::RETI() {                              // RETI
  this->IME = true;
  this->RET();
}

void CPU::RST(uint8_t vec) {                     // RST vec
  this->CALL(vec);
}

/* Stack Operations Instructions */

void CPU::ADDSP(int8_t e8) {                     // ADD SP, e8
  uint16_t result = this->SP + e8;

  // Set Flags
  this->setZeroFlag(false);
  this->setAddSubFlag(false);
  this->checkHalfCarry(this->SP >> 8, result >> 8);
  this->checkCarry(this->SP >> 8, result >> 8);

  this->SP = result;
}

void CPU::DECSP() {                              // DEC SP
  this->SP -= 1;
}

void CPU::INCSP() {                              // INC SP
  this->SP += 1;
}

void CPU::LDSP(uint16_t u16) {                   // LD SP, u16 | LD SP, HL
  this->SP = u16;
}

void CPU::LDSP_MEM(uint16_t a16) {               // LD [u16], SP
  this->memory.write(a16, uint8_t (this->SP & 0xFF));
  this->memory.write(a16 + 1, uint8_t (this->SP >> 8));
}

void CPU::LDHL(int8_t e8) {                      // LD HL, SP+e8
  uint16_t result = this->SP + e8;

  // Set Flags
  this->setZeroFlag(false);
  this->setAddSubFlag(false);
  this->checkHalfCarry(this->SP >> 8, result >> 8);
  this->checkCarry(this->SP >> 8, result >> 8);

  // Store into HL
  this->reg.H = this->SP << 8;
  this->reg.L = this->SP & 0xFF;
}

void CPU::POPAF() {                              // POP AF
  this->reg.F = this->memory.read(this->SP++);
  this->reg.A = this->memory.read(this->SP++);
}

void CPU::POP(uint16_t *r16) {                   // POP r16
  *r16 = this->memory.read(this->SP++) | (this->memory.read(this->SP++) << 8);
}

void CPU::PUSHAF() {                             // PUSH AF
  this->memory.write(--SP, this->reg.A);
  this->memory.write(--SP, this->reg.F);
}

void CPU::PUSH(uint16_t *r16) {                  // PUSH r16
  this->memory.write(--SP, uint8_t(*r16 >> 8));
  this->memory.write(--SP, uint8_t(*r16 & 0xFF));
}

/* Miscellaneous Instructions */

void CPU::CCF() {                                // CCF
  // Set Flags
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
  this->reg.F ^= 0x10;
}

void CPU::CPL() {                                // CPL
  this->reg.A = ~this->reg.A;

  // Set Flags
  this->setZeroFlag(false);
  this->setHalfCarryFlag(false);
}

// TODO: Implement after thorough research
void CPU::DAA() {                                // DAA
  std::cout << "DAA: Implement me!\n";
}

void CPU::DI() {                                 // DI
  this->IME = false;
}

void CPU::EI() {                                 // EI
  this->IME = true;
}

void CPU::HALT() {                               // HALT
  this->halted = true;
}

void CPU::SCF() {                                // SCF
  // Set Flags
  this->setAddSubFlag(false);
  this->setHalfCarryFlag(false);
  this->setCarryFlag(true);
}
