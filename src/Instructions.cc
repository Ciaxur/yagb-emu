#include "../include/CPU.h"

/* 8-bit Arithmetic and Logic Instructions */

void CPU::ADC(uint8_t *r8) {                // ADC A, r8
  this->ADC(*r8);
}

void CPU::ADC(uint16_t a16) {               // ADC A, [HL]
  this->ADC(this->memory.read(a16));
}

void CPU::ADC(uint8_t u8) {                 // ADC A, u8
  uint8_t result = this->reg.A + ((this->reg.F & 0x10) >> 4) + u8;

  // Set Flags
  this->setZeroFlag(result == 0);     // Zero Flag
  this->setAddSubFlag(false);   // Unset N Flag
  this->checkHalfCarry(result, this->reg.A);
  this->checkCarry(this->reg.A, result);

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
  this->setZeroFlag(result == 0);     // Zero Flag
  this->setAddSubFlag(false);   // Unset N Flag
  this->checkHalfCarry(result, this->reg.A);
  this->checkCarry(this->reg.A, result);

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
  this->setZeroFlag(result == 0);     // Zero Flag
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
  this->setZeroFlag(result == 0);     // Zero Flag
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->reg.A, result); // Set if borrow from bit 4
  this->checkCarry(u8, this->reg.A); // Set if borrow
}

void CPU::DEC(uint8_t *r8) {                // DEC r8
  uint8_t result = *r8 - 1;

  // Set Flags
  this->setZeroFlag(result == 0);   // Zero Flag
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(*r8, result); // Set if borrow from bit 4

  // New r8 value
  *r8 = result;
}

void CPU::DEC(uint16_t a16) {               // DEC [HL]
  uint8_t result = this->memory.read(a16) - 1;

  // Set Flags
  this->setZeroFlag(result == 0);   // Zero Flag
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->memory.read(a16), result); // Set if borrow from bit 4

  this->memory.write(a16, result);
}

void CPU::INC(uint8_t *r8) {                // INC r8
  uint8_t result = *r8 + 1;

  // Set Flags
  this->setZeroFlag(result == 0);   // Zero Flag
  this->setAddSubFlag(false);       // Unset N Flag
  this->checkHalfCarry(*r8, result);     // Set if overflow from bit 3

  // New r8 value
  *r8 = result;
}

void CPU::INC(uint16_t a16) {               // INC [HL]
  uint8_t result = this->memory.read(a16) + 1;

  // Set Flags
  this->setZeroFlag(result == 0);   // Zero Flag
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
  this->setZeroFlag(result == 0);     // Zero Flag

  this->reg.A = result;
}

void CPU::SBC(uint8_t *r8) {                // SBC A, r8
  this->SBC(*r8);
}

void CPU::SBC(uint16_t a16) {               // SBC A, [HL]
  this->SBC(this->memory.read(a16));
}

void CPU::SBC(uint8_t u8) {                 // SBC A, u8
  uint8_t result = this->reg.A - u8 - ((this->reg.F & 0x10) >> 4);

  // Set Flags
  this->setZeroFlag(result == 0);     // Zero Flag
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->reg.A, result);
  this->checkCarry(u8 + ((this->reg.F & 0x10) >> 4), this->reg.A);  // Check Carry for Subtraction

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
  this->setZeroFlag(result == 0);      // Zero Flag
  this->setAddSubFlag(true);  // Set N Flag
  this->checkHalfCarry(this->reg.A, result);
  this->checkCarry(u8, this->reg.A);  // Check Carry for Subtraction

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
  this->setZeroFlag(result == 0);     // Zero Flag

  this->reg.A = result;
}

/* 16-bit Arithmetic Instructions */

void CPU::ADDHL(uint16_t r16) {             // ADD HL, r16
  uint16_t HL = (this->reg.H << 8) | this->reg.L;
  uint16_t result = HL + r16;

  // Set Flags
  this->setAddSubFlag(false);  // Unset N Flag
  this->checkHalfCarry(HL >> 8, result >> 8);
  this->checkCarry_16(HL, HL + r16);

  this->reg.H = result >> 8;
  this->reg.L = result & 0xFF;
}

void CPU::DEC(uint8_t *ru, uint8_t *rl) {    // DEC r16
  uint16_t r16 = (*ru << 8) | *rl;
  uint16_t result = r16 - 1;

  *ru = result >> 8;
  *rl = result & 0xFF;
}

void CPU::INC(uint8_t *ru, uint8_t *rl) {    // INC r16
  uint16_t r16 = (*ru << 8) | *rl;
  uint16_t result = r16 + 1;

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
  this->setZeroFlag(result == 0);     // Zero Flag
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
  uint8_t carry = (this->reg.F & 0x10) << 3;

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
  *r8 = (*r8 << 1) | ((this->reg.F & 0x10) >> 4);

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
  uint8_t carry = (this->reg.F & 0x10) << 3; // Set to Top Bit

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
  this->RR(&this->reg.A);
  this->setZeroFlag(false);
}

void CPU::RRC(uint8_t *r8) {                // RRC r8
  // Set Carry flag according to 7th Bit
  this->setCarryFlag((*r8 & 0x01) != 0);

  // Carry 7th Bit over
  *r8 = (*r8 >> 1) | ((this->reg.F & 0x10) << 3);

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

void CPU::LD(uint16_t a16) {                // LD [r16], A | LD [u16], A | LDH [u16], A | LDH [C], A
  this->memory.write(a16, this->reg.A);
}

void CPU::LDA(uint16_t a16) {               // LD A, [r16] | LD A, [u16] | LDH A, [u16] | LDH A, [C]
  this->reg.A = this->memory.read(a16);
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
  uint16_t offsetAddr = this->PC + 0x03;        // Offset from CALL
  this->PUSH(&offsetAddr);

  // JP to address
  this->PC = u16 - 0x03;
}

void CPU::CALL(ConditionCode cc, uint16_t a16) {   // CALL cc, u16
  this->extraCycles = 3;

  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        return this->CALL(a16);
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        return this->CALL(a16);
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        return this->CALL(a16);
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        return this->CALL(a16);
      break;
  }

  this->extraCycles = 0;
}

void CPU::JP(uint16_t a16) {                    // JP u16
  this->PC = a16 - 0x03;
}

void CPU::JPHL(uint16_t a16) {                  // JP HL
  this->PC = a16 - 0x01;
}

void CPU::JP(ConditionCode cc, uint16_t a16) {  // JP cc, u16
  this->extraCycles = 1;

  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        return this->JP(a16);
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        return this->JP(a16);
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        return this->JP(a16);
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        return this->JP(a16);
      break;
  }

  this->extraCycles = 0;
}

void CPU::JR(int8_t e8) {                       // JR e8
  this->PC = static_cast<uint16_t>(e8 + this->PC);
}

void CPU::JR(ConditionCode cc, int8_t e8) {     // JR cc, e8
  this->extraCycles = 1;

  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        return this->JR(e8);
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        return this->JR(e8);
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        return this->JR(e8);
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        return this->JR(e8);
      break;
  }

  this->extraCycles = 0;
}

void CPU::RET(ConditionCode cc) {                 // RET cc
  this->extraCycles = 3;

  switch (cc) {
    case Z:
      if ((this->reg.F & 0x80) != 0)
        return this->RET();
      break;
    case NZ:
      if ((this->reg.F & 0x80) == 0)
        return this->RET();
      break;
    case C:
      if ((this->reg.F & 0x10) != 0)
        return this->RET();
      break;
    case NC:
      if ((this->reg.F & 0x10) == 0)
        return this->RET();
      break;
  }

  this->extraCycles = 0;
}

void CPU::RET() {                                // RET
  this->POP(&this->PC);
  this->PC -= 0x01;
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
  this->checkCarry_16(SP, SP + e8);

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
  this->checkCarry_16(SP, SP + e8);

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

void CPU::POP(uint8_t *ru, uint8_t *rl) {        // POP r16
  *rl = this->memory.read(this->SP++);  // Lower First (Little Endian)
  *ru = this->memory.read(this->SP++);
}

void CPU::PUSHAF() {                             // PUSH AF
  this->memory.write(--SP, this->reg.A);
  this->memory.write(--SP, this->reg.F & 0xF0); // ANNOYING AF
}

void CPU::PUSH(uint16_t *r16) {                  // PUSH r16
  this->memory.write(--SP, uint8_t(*r16 >> 8));
  this->memory.write(--SP, uint8_t(*r16 & 0xFF));
}

void CPU::PUSH(uint8_t *ru, uint8_t *rl) {       // PUSH r16
  this->memory.write(--SP, *ru);
  this->memory.write(--SP, *rl);
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

void CPU::DAA() {                                // DAA
  uint8_t A = this->reg.A;
  bool isAddedSix = false;

  // Addition
  if (!(this->reg.F & 0x40)) {
    if (this->reg.F & 0x20 || (A & 0x0F) > 0x09) {
      A += 0x06;
      isAddedSix = true;
    }
    if (this->reg.F & 0x10 || A > 0x9F || isAddedSix && A < 0x06) { // PATCHED END: If overflow from prev A
      A += 0x60;
      this->setCarryFlag(true);
    }
  }
  
  // Subtraction
  else {
    if (this->reg.F & 0x20) {
      A -= 0x06;
    }
    if (this->reg.F & 0x10) {
      A -= 0x60;
    }
  }

  this->setZeroFlag(A == 0);
  this->setHalfCarryFlag(false);

  // Set the Value
  this->reg.A = A;
}

void CPU::DI() {                                 // DI
  this->IME = false;
}

void CPU::EI() {                                 // EI
  this->delayed_IME = true;
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
