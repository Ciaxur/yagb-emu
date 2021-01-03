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
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->LD(&(cpu->reg.B), &(cpu->reg.C), u16);
  });
  cpu->oMap[0x02] = new Opcode(0x02, "LD (BC), A", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.C << 8) | cpu->reg.B;
    cpu->LD(a16, &(cpu->reg.A));
  });
  cpu->oMap[0x03] = new Opcode(0x03, "INC BC", 2, 1, [&]() {
    cpu->INC(&(cpu->reg.B), &(cpu->reg.C));
  });
  cpu->oMap[0x04] = new Opcode(0x04, "INC B", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.B));
  });
  cpu->oMap[0x05] = new Opcode (0x05, "DEC B", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.B));
  });
  cpu->oMap[0x06] = new Opcode(0x06, "LD, B, u8", 2, 2, [&]() {
    cpu->LD(&(cpu->reg.B), cpu->memory.read(cpu->PC + 1));
  });
  cpu->oMap[0x07] = new Opcode(0x07, "RLCA", 1, 1, [&]() {
    cpu->RLCA();
  });
  cpu->oMap[0x08] = new Opcode(0x08, "LD (u16), SP", 5, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->LDSP_MEM(u16);
  });
  cpu->oMap[0x09] = new Opcode(0x09, "ADD HL, BC", 2, 1, [&]() {
    uint16_t r16 = (cpu->reg.B << 8) | cpu->reg.C;
    cpu->ADDHL(r16);
  });
  cpu->oMap[0x0A] = new Opcode(0x0A, "LD A, (BC)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.B << 8) | cpu->reg.C;
    cpu->LDA(a16);
  });
  cpu->oMap[0x0B] = new Opcode(0x0B, "DEC BC", 2, 1, [&]() {
    cpu->DEC(&(cpu->reg.B), &(cpu->reg.C));
  });
  cpu->oMap[0x0C] = new Opcode(0x0C, "INC C", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.C));
  });
  cpu->oMap[0x0D] = new Opcode(0x0D, "DEC C", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.C));
  });
  cpu->oMap[0x0E] = new Opcode(0x0E, "LD C, u8", 2, 2, [&]() {
    cpu->LD(&(cpu->reg.C), cpu->memory.read(cpu->PC + 1));
  });
  cpu->oMap[0x0F] = new Opcode(0x0F, "RRCA", 1, 1, [&]() {
    cpu->RRCA();
  });

  // 10 - 1F
  cpu->oMap[0x10] = new Opcode(0x10, "STOP", 1, 2, [&]() {});

  // 20 - 2F

}

// TODO:
void CPU::initPrefixed(CPU* cpu) {}
