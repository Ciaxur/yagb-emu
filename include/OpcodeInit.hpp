#pragma once
#include <unordered_map>
#include <string>
#include "./CPU.h"
#include "./Opcode.h"

// TODO:
void CPU::initOpcodes(CPU* cpu) {
  // 00 - 0F
  cpu->oMap[0x00] = new Opcode (0x00, "NOP", 1, 1, [&]() {});
  cpu->oMap[0x01] = new Opcode (0x01, "LD BC, u16", 3, 3, [&]() {
      cpu->reg.B = cpu->memory.read(cpu->PC + 2);
      cpu->reg.C = cpu->memory.read(cpu->PC + 1);
  });
  cpu->oMap[0x02] = new Opcode (0x02, "LD (BC), A", 2, 1, [&]() {
      uint16_t BC = (cpu->reg.C << 8) | cpu->reg.B;
      cpu->memory.write(BC, cpu->reg.A);
  });
  cpu->oMap[0x03] = new Opcode (0x03, "INC BC", 2, 1, [&]() {
      uint16_t BC = ((cpu->reg.C << 8) | cpu->reg.B) + 0x01;
      cpu->reg.B = (BC & 0xFF00) >> 8;  // Would "BC >> 8" instead not cause any issues?
      cpu->reg.C = BC & 0x00FF;
  });
  cpu->oMap[0x04] = new Opcode (0x04, "INC B", 1, 1, [&]() {
      // New B Value
      uint8_t B = cpu->reg.B + 1;

      // Set Zero Flag
      if (B == 0)
        cpu->reg.F |= 0x80;
      
      // Unset Neg. Flag
      cpu->reg.F &= 0xFB;

      
      // Half Carry
      cpu->checkHalfCarry(cpu->reg.B, B);

      // Set New B Value
      cpu->reg.B = B;
  });
  cpu->oMap[0x05] = new Opcode (0x05, "DEC B", 1, 1, [&]() {
    uint8_t B = cpu->reg.B - 1;

    // Flags
    if (B == 0)   // Zero Flag
      cpu->reg.F |= 0x80;

    // Set Negative Flag
    cpu->reg.F |= 0x40;

    // Half Carry
    cpu->checkHalfCarry(cpu->reg.B, B);

    // Set new B Reg Value
    cpu->reg.B = B;
  });
  cpu->oMap[0x06] = new Opcode(0x06, "LD, B, u8", 2, 2, [&]() {
    cpu->reg.B = cpu->memory.read(cpu->PC);
  });
  cpu->oMap[0x07] = new Opcode(0x07, "RLCA", 1, 1, [&]() {
    // Reset Flags
    cpu->reg.F = 0x00;
    
    uint8_t A = cpu->reg.A;
    if (A & 0x80) {         // Left Most Bit
      A = (A << 1) | 0x01;  // Set right most bit
      cpu->reg.F |= 0x01;   // There was a carry
    } else {
      A = A << 1;           // No Carry
    }
    cpu->reg.A = A;
  });


  // 10 - 1F

  // 20 - 2F

}

// TODO:
void CPU::initPrefixed(CPU* cpu) {}
