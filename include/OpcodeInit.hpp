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
    uint16_t a16 = (cpu->reg.B << 8) | cpu->reg.C;
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
  cpu->oMap[0x11] = new Opcode(0x11, "LD DE, u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->LD(&(cpu->reg.D), &(cpu->reg.E), u16);
  });
  cpu->oMap[0x12] = new Opcode(0x12, "LD (DE), A", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.D << 8) | cpu->reg.E;
    cpu->LD(a16, &(cpu->reg.A));
  });
  cpu->oMap[0x13] = new Opcode(0x13, "INC DE", 2, 1, [&]() {
    cpu->INC(&(cpu->reg.D), &(cpu->reg.E));
  });
  cpu->oMap[0x14] = new Opcode(0x14, "INC C", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.C));
  });
  cpu->oMap[0x15] = new Opcode(0x15, "DEC C", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.C));
  });
  cpu->oMap[0x16] = new Opcode(0x16, "LD D, u8", 2, 2, [&]() {
    cpu->LD(&(cpu->reg.D), cpu->memory.read(cpu->PC + 1));
  });
  cpu->oMap[0x17] = new Opcode(0x17, "RLA", 1, 1, [&]() {
    cpu->RLA();
  });
  cpu->oMap[0x18] = new Opcode(0x18, "JR e8", 3, 2, [&]() {
    int8_t e8 = cpu->memory.read(cpu->PC + 1);
    cpu->JR(e8);
  });
  cpu->oMap[0x19] = new Opcode(0x19, "ADD HL, DE", 2, 1, [&]() {
    uint16_t r16 = (cpu->reg.D << 8) | cpu->reg.E;
    cpu->ADDHL(r16);
  });
  cpu->oMap[0x1A] = new Opcode(0x1A, "LD A, (DE)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.D << 8) | cpu->reg.E;
    cpu->LDA(a16);
  });
  cpu->oMap[0x1B] = new Opcode(0x1B, "DEC DE", 2, 1, [&]() {
    cpu->DEC(&(cpu->reg.B), &(cpu->reg.C));
  });
  cpu->oMap[0x1C] = new Opcode(0x1C, "INC E", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.E));
  });
  cpu->oMap[0x1D] = new Opcode(0x1D, "DEC E", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.E));
  });
  cpu->oMap[0x1E] = new Opcode(0x1E, "LD E, u8", 2, 2, [&]() {
    cpu->LD(&(cpu->reg.E), cpu->memory.read(cpu->PC + 1));
  });
  cpu->oMap[0x1F] = new Opcode(0x1F, "RRA", 1, 1, [&]() {
    cpu->RRA();
  });

  // 20 - 2F
  cpu->oMap[0x20] = new Opcode(0x20, "JR NZ, e8", 2, 2, [&]() {
    int8_t e8 = cpu->memory.read(cpu->PC + 1);
    cpu->JR(ConditionCode::NZ, e8);
  });
  cpu->oMap[0x21] = new Opcode(0x21, "LD HL,u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->LD(&(cpu->reg.H), &(cpu->reg.L), u16);
  });
  cpu->oMap[0x22] = new Opcode(0x22, "LD (HL+), A", 2, 1, [&]() {
    cpu->LDHLI();
  });
  cpu->oMap[0x23] = new Opcode(0x23, "INC HL", 2, 1, [&]() {
    cpu->INC(&(cpu->reg.H), &(cpu->reg.L));
  });
  cpu->oMap[0x24] = new Opcode(0x24, "INC H", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.H));
  });
  cpu->oMap[0x25] = new Opcode(0x25, "DEC H", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.H));
  });
  cpu->oMap[0x26] = new Opcode(0x26, "LD H, u8", 2, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->LD(&(cpu->reg.H), u8);
  });
  cpu->oMap[0x27] = new Opcode(0x27, "DAA", 1, 1, [&]() {
    cpu->DAA();
  });
  cpu->oMap[0x28] = new Opcode(0x28, "JR Z, e8", 2, 2, [&]() {
    int8_t e8 = cpu->memory.read(cpu->PC + 1);
    cpu->JR(ConditionCode::Z, e8);
  });
  cpu->oMap[0x29] = new Opcode(0x29, "ADD HL, HL", 2, 1, [&]() {
    uint16_t HL = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->ADDHL(HL);
  });
  cpu->oMap[0x2A] = new Opcode(0x2A, "LD A, (HL+)", 2, 1, [&]() {
    cpu->LDAHLI();
  });
  cpu->oMap[0x2B] = new Opcode(0x2B, "DEC HL", 2, 1, [&]() {
    cpu->DEC(&(cpu->reg.H), &(cpu->reg.L));
  });
  cpu->oMap[0x2C] = new Opcode(0x2C, "INC L", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.L));
  });
  cpu->oMap[0x2D] = new Opcode(0x2D, "DEC L", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.L));
  });
  cpu->oMap[0x2E] = new Opcode(0x2E, "LD L, u8", 2, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->LD(&(cpu->reg.L), u8);
  });
  cpu->oMap[0x2F] = new Opcode(0x2F, "CPL", 1, 1, [&]() {
    cpu->CPL();
  });

  // 30 - 3F
  cpu->oMap[0x30] = new Opcode(0x30, "JR NC, e8", 3, 2, [&]() {
    int8_t e8 = cpu->memory.read(cpu->PC + 1);
    cpu->JR(ConditionCode::NC, e8);
  });
  cpu->oMap[0x31] = new Opcode(0x31, "LD SP, u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->LDSP(u16);
  });
  cpu->oMap[0x32] = new Opcode(0x32, "LD (HL-), A", 2, 1, [&]() {
    cpu->LDHLD();
  });
  cpu->oMap[0x33] = new Opcode(0x33, "INC SP", 2, 1, [&]() {
    cpu->INCSP();
  });
  cpu->oMap[0x34] = new Opcode(0x34, "INC (HL)", 3, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->INC(a16);
  });
  cpu->oMap[0x35] = new Opcode(0x35, "DEC (HL)", 3, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->DEC(a16);
  });
  cpu->oMap[0x36] = new Opcode(0x36, "LD (HL), u8", 3, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->LD(a16, u8);
  });
  cpu->oMap[0x37] = new Opcode(0x37, "SCF", 1, 1, [&]() {
    cpu->SCF();
  });
  cpu->oMap[0x38] = new Opcode(0x38, "JR C, e8", 2, 2, [&]() {
    int8_t e8 = cpu->memory.read(cpu->PC + 1);
    cpu->JR(ConditionCode::C, e8);
  });
  cpu->oMap[0x39] = new Opcode(0x39, "ADD HL, SP", 2, 1, [&]() {
    cpu->ADDHL(cpu->SP);
  });
  cpu->oMap[0x3A] = new Opcode(0x3A, "LD A, (HL-)", 2, 1, [&]() {
    cpu->LDAHLD();
  });
  cpu->oMap[0x3B] = new Opcode(0x3B, "DEC SP", 2, 1, [&]() {
    cpu->DECSP();
  });
  cpu->oMap[0x3C] = new Opcode(0x3C, "INC A", 1, 1, [&]() {
    cpu->INC(&(cpu->reg.A));
  });
  cpu->oMap[0x3D] = new Opcode(0x3D, "DEC A", 1, 1, [&]() {
    cpu->DEC(&(cpu->reg.A));
  });
  cpu->oMap[0x3E] = new Opcode(0x3E, "LD A, u8", 2, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->LD(&(cpu->reg.A), u8);
  });
  cpu->oMap[0x3F] = new Opcode(0x3F, "CCF", 1, 1, [&]() {
    cpu->CCF();
  });

  // 40 - 4F
  cpu->oMap[0x40] = new Opcode(0x40, "LD B, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.B));
  });
  cpu->oMap[0x41] = new Opcode(0x41, "LD B, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.C));
  });
  cpu->oMap[0x42] = new Opcode(0x42, "LD B, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.D));
  });
  cpu->oMap[0x43] = new Opcode(0x43, "LD B, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.E));
  });
  cpu->oMap[0x44] = new Opcode(0x44, "LD B, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.H));
  });
  cpu->oMap[0x45] = new Opcode(0x45, "LD B, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.L));
  });
  cpu->oMap[0x46] = new Opcode(0x46, "LD B, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.B), a16);
  });
  cpu->oMap[0x47] = new Opcode(0x47, "LD B, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.B), &(cpu->reg.A));
  });
  cpu->oMap[0x48] = new Opcode(0x48, "LD C, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.B));
  });
  cpu->oMap[0x49] = new Opcode(0x49, "LD C, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.C));
  });
  cpu->oMap[0x4A] = new Opcode(0x4A, "LD C, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.D));
  });
  cpu->oMap[0x4B] = new Opcode(0x4B, "LD C, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.E));
  });
  cpu->oMap[0x4C] = new Opcode(0x4C, "LD C, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.H));
  });
  cpu->oMap[0x4D] = new Opcode(0x4D, "LD C, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.L));
  });
  cpu->oMap[0x4E] = new Opcode(0x4E, "LD C, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.C), a16);
  });
  cpu->oMap[0x4F] = new Opcode(0x4F, "LD C, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.C), &(cpu->reg.A));
  });

  // 50 - 5F

  // 60 - 6F
  cpu->oMap[0x60] = new Opcode(0x60, "LD H, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.B));
  });
  cpu->oMap[0x61] = new Opcode(0x61, "LD H, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.C));
  });
  cpu->oMap[0x62] = new Opcode(0x62, "LD H, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.D));
  });
  cpu->oMap[0x63] = new Opcode(0x63, "LD H, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.E));
  });
  cpu->oMap[0x64] = new Opcode(0x64, "LD H, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.H));
  });
  cpu->oMap[0x65] = new Opcode(0x65, "LD H, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.L));
  });
  cpu->oMap[0x66] = new Opcode(0x66, "LD H, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.H), a16);
  });
  cpu->oMap[0x67] = new Opcode(0x67, "LD H, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.H), &(cpu->reg.A));
  });
  cpu->oMap[0x68] = new Opcode(0x68, "LD L, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.B));
  });
  cpu->oMap[0x69] = new Opcode(0x69, "LD L, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.C));
  });
  cpu->oMap[0x6A] = new Opcode(0x6A, "LD L, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.D));
  });
  cpu->oMap[0x6B] = new Opcode(0x6B, "LD L, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.E));
  });
  cpu->oMap[0x6C] = new Opcode(0x6C, "LD L, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.H));
  });
  cpu->oMap[0x6D] = new Opcode(0x6D, "LD L, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.L));
  });
  cpu->oMap[0x6E] = new Opcode(0x6E, "LD L, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.L), a16);
  });
  cpu->oMap[0x6F] = new Opcode(0x6F, "LD L, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.L), &(cpu->reg.A));
  });
}

// TODO:
void CPU::initPrefixed(CPU* cpu) {}
