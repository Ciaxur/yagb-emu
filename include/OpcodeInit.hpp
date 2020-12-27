#pragma once
#include <unordered_map>
#include <string>
#include "./CPU.h"
#include "./Opcode.h"

// TODO:
void CPU::initOpcodes(CPU* cpu) {
  // 00 - 0F
  cpu->oMap[0x00] = new Opcode(0x00, "NOP", 1, 1, [&]() {});
  cpu->oMap[0x01] = new Opcode(0x01, "LD BC, u16", 3, 3, [&]() {
    cpu->reg.B = cpu->memory.read(cpu->PC + 2);
    cpu->reg.C = cpu->memory.read(cpu->PC + 1);
  });
  cpu->oMap[0x02] = new Opcode(0x02, "LD (BC), A", 2, 1, [&]() {
    uint16_t BC = (cpu->reg.C << 8) | cpu->reg.B;
    cpu->memory.write(BC, cpu->reg.A);
  });
  cpu->oMap[0x03] = new Opcode(0x03, "INC BC", 2, 1, [&]() {
    uint16_t BC = ((cpu->reg.C << 8) | cpu->reg.B) + 0x01;
    cpu->reg.B =
        (BC & 0xFF00) >> 8; // Would "BC >> 8" instead not cause any issues?
    cpu->reg.C = BC & 0x00FF;
  });
  cpu->oMap[0x04] = new Opcode(0x04, "INC B", 1, 1, [&]() {
    // New B Value
    uint8_t B = cpu->reg.B + 1;

    // Set Zero Flag
    if (B == 0)
      cpu->reg.F |= 0x80;

    // Unset Neg. Flag
    cpu->reg.F &= 0x7F;

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
    cpu->reg.B = cpu->memory.read(cpu->PC + 1);
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
  cpu->oMap[0x08] = new Opcode(0x08, "LD (u16), SP", 5, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);

    cpu->memory.write(u16, cpu->SP);
  });
  cpu->oMap[0x09] = new Opcode(0x09, "ADD HL, BC", 2, 1, [&]() {
    uint16_t BC = (cpu->reg.B << 8) | cpu->reg.C;
    uint16_t HL = (cpu->reg.H << 8) | cpu->reg.L;
    uint16_t result = BC + HL;

    cpu->reg.F &= 0x7F;
    cpu->checkHalfCarry(HL >> 8, result >> 8);
    cpu->checkCarry(HL >> 8, result >> 8);

    cpu->reg.H = result >> 8;
    cpu->reg.L = result & 0xFF;
  });
  cpu->oMap[0x0A] = new Opcode(0x0A, "LD A, (BC)", 2, 1, [&]() {
    uint16_t BC = (cpu->reg.B << 8) | cpu->reg.C;

    cpu->reg.A = cpu->memory.read(BC);
  });
  cpu->oMap[0x0B] = new Opcode(0x0B, "DEC BC", 2, 1, [&]() {
    uint16_t BC = (cpu->reg.B << 8) | cpu->reg.C;
    uint16_t result = --BC;

    cpu->reg.B = result >> 8;
    cpu->reg.C = result & 0xFF;
  });
  cpu->oMap[0x0C] = new Opcode(0x0C, "INC C", 1, 1, [&]() {
    uint8_t C = cpu->reg.C + 1;

    if (C == 0)
      cpu->reg.F |= 0x80;
    cpu->reg.F &= 0x7F;
    cpu->checkHalfCarry(cpu->reg.C, C);

    cpu->reg.C = C;
  });
  cpu->oMap[0x0D] = new Opcode(0x0D, "DEC C", 1, 1, [&]() {
      uint8_t C = cpu->reg.C - 1;

      if (C == 0)
        cpu->reg.F |= 0x80;
      cpu->reg.F |= 0x40;
      cpu->checkHalfCarry(cpu->reg.C, C);

      cpu->reg.C = C;
  });
  cpu->oMap[0x0E] = new Opcode(0x0E, "LD C, u8", 2, 2, [&]() {
    cpu->reg.C = cpu->memory.read(cpu->PC + 1);
  });
  cpu->oMap[0x0F] = new Opcode(0x0F, "RRCA", 1, 1, [&]() {
    cpu->reg.F = 0x00;

    uint8_t A = cpu->reg.A;
    if (A & 0x01) {
      A = (A >> 1) | 0x01;
      cpu->reg.F |= 0x01;
    } else {
      A = A >> 1;
    }

    cpu->reg.A = A;
  });

  // 10 - 1F

  // 20 - 2F

}

// TODO:
void CPU::initPrefixed(CPU* cpu) {}
