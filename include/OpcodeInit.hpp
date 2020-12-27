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

      // Unset Neg. Flag
      cpu->reg.F &= 0xFB;

      // Set Zero Flag
      if (B == 0)
        cpu->reg.F |= 0x80;

      // Half Carry
      if (cpu->reg.B <= 0x0F && B > 0x0F)
        cpu->reg.F |= 0x02;

      // Set New B Value
      cpu->reg.B = B;
  });

  // 10 - 1F

  // 20 - 2F

}

// TODO:
void CPU::initPrefixed(CPU* cpu) {}
