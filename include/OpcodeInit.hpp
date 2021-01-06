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
  cpu->oMap[0x50] = new Opcode(0x50, "LD D, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.B));
  });
  cpu->oMap[0x51] = new Opcode(0x51, "LD D, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.C));
  });
  cpu->oMap[0x52] = new Opcode(0x52, "LD D, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.D));
  });
  cpu->oMap[0x53] = new Opcode(0x53, "LD D, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.E));
  });
  cpu->oMap[0x54] = new Opcode(0x54, "LD D, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.H));
  });
  cpu->oMap[0x55] = new Opcode(0x55, "LD D, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.L));
  });
  cpu->oMap[0x56] = new Opcode(0x56, "LD D, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.D), a16);
  });
  cpu->oMap[0x57] = new Opcode(0x57, "LD D, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.D), &(cpu->reg.A));
  });
  cpu->oMap[0x58] = new Opcode(0x58, "LD E, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.B));
  });
  cpu->oMap[0x59] = new Opcode(0x59, "LD E, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.C));
  });
  cpu->oMap[0x5A] = new Opcode(0x5A, "LD E, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.D));
  });
  cpu->oMap[0x5B] = new Opcode(0x5B, "LD E, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.E));
  });
  cpu->oMap[0x5C] = new Opcode(0x5C, "LD E, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.H));
  });
  cpu->oMap[0x5D] = new Opcode(0x5D, "LD E, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.L));
  });
  cpu->oMap[0x5E] = new Opcode(0x5E, "LD E, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.E), a16);
  });
  cpu->oMap[0x5F] = new Opcode(0x5F, "LD E, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.E), &(cpu->reg.A));
  });

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

  // 70 - 7F
  cpu->oMap[0x70] = new Opcode(0x70, "LD (HL), B", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.B));
  });
  cpu->oMap[0x71] = new Opcode(0x71, "LD (HL), C", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.C));
  });
  cpu->oMap[0x72] = new Opcode(0x72, "LD (HL), D", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.D));
  });
  cpu->oMap[0x73] = new Opcode(0x73, "LD (HL), E", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.E));
  });
  cpu->oMap[0x74] = new Opcode(0x74, "LD (HL), H", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.H));
  });
  cpu->oMap[0x75] = new Opcode(0x75, "LD (HL), L", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.L));
  });
  cpu->oMap[0x76] = new Opcode(0x76, "HALT", 1, 1, [&]() {
    cpu->HALT();
  });
  cpu->oMap[0x77] = new Opcode(0x77, "LD (HL), A", 1, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(a16, &(cpu->reg.A));
  });
  cpu->oMap[0x78] = new Opcode(0x78, "LD A, B", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.B));
  });
  cpu->oMap[0x79] = new Opcode(0x79, "LD A, C", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.C));
  });
  cpu->oMap[0x7A] = new Opcode(0x7A, "LD A, D", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.D));
  });
  cpu->oMap[0x7B] = new Opcode(0x7B, "LD A, E", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.E));
  });
  cpu->oMap[0x7C] = new Opcode(0x7C, "LD A, H", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.H));
  });
  cpu->oMap[0x7D] = new Opcode(0x7D, "LD A, L", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.L));
  });
  cpu->oMap[0x7E] = new Opcode(0x7E, "LD A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->LD(&(cpu->reg.A), a16);
  });
  cpu->oMap[0x7F] = new Opcode(0x7F, "LD A, A", 1, 1, [&]() {
    cpu->LD(&(cpu->reg.A), &(cpu->reg.A));
  });

  // 80 - 8F
  cpu->oMap[0x80] = new Opcode(0x80, "ADD A, B", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.B));
  });
  cpu->oMap[0x81] = new Opcode(0x81, "ADD A, C", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.C));
  });
  cpu->oMap[0x82] = new Opcode(0x82, "ADD A, D", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.D));
  });
  cpu->oMap[0x83] = new Opcode(0x83, "ADD A, E", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.E));
  });
  cpu->oMap[0x84] = new Opcode(0x84, "ADD A, H", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.H));
  });
  cpu->oMap[0x85] = new Opcode(0x85, "ADD A, L", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.L));
  });
  cpu->oMap[0x86] = new Opcode(0x86, "ADD A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->ADD(a16);
  });
  cpu->oMap[0x87] = new Opcode(0x87, "ADD A, A", 1, 1, [&]() {
    cpu->ADD(&(cpu->reg.A));
  });
  cpu->oMap[0x88] = new Opcode(0x88, "ADC A, B", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.B));
  });
  cpu->oMap[0x89] = new Opcode(0x89, "ADC A, C", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.C));
  });
  cpu->oMap[0x8A] = new Opcode(0x8A, "ADC A, D", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.D));
  });
  cpu->oMap[0x8B] = new Opcode(0x8B, "ADC A, E", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.E));
  });
  cpu->oMap[0x8C] = new Opcode(0x8C, "ADC A, H", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.H));
  });
  cpu->oMap[0x8D] = new Opcode(0x8D, "ADC A, L", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.L));
  });
  cpu->oMap[0x8E] = new Opcode(0x8E, "ADC A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->ADC(a16);
  });
  cpu->oMap[0x8F] = new Opcode(0x8F, "ADC A, A", 1, 1, [&]() {
    cpu->ADC(&(cpu->reg.A));
  });

  // 90 - 9F
  cpu->oMap[0x90] = new Opcode(0x90, "SUB A, B", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.B));
  });
  cpu->oMap[0x91] = new Opcode(0x91, "SUB A C", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.C));
  });
  cpu->oMap[0x92] = new Opcode(0x92, "SUB A, D", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.D));
  });
  cpu->oMap[0x93] = new Opcode(0x93, "SUB A, E", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.E));
  });
  cpu->oMap[0x94] = new Opcode(0x94, "SUB A, H", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.H));
  });
  cpu->oMap[0x95] = new Opcode(0x95, "SUB A, L", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.L));
  });
  cpu->oMap[0x96] = new Opcode(0x96, "SUB A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SUB(a16);
  });
  cpu->oMap[0x97] = new Opcode(0x97, "SUB A, A", 1, 1, [&]() {
    cpu->SUB(&(cpu->reg.A));
  });
  cpu->oMap[0x98] = new Opcode(0x98, "SBC A, B", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.B));
  });
  cpu->oMap[0x99] = new Opcode(0x99, "SBC A, C", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.C));
  });
  cpu->oMap[0x9A] = new Opcode(0x9A, "SBC A, D", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.D));
  });
  cpu->oMap[0x9B] = new Opcode(0x9B, "SBC A, E", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.E));
  });
  cpu->oMap[0x9C] = new Opcode(0x9C, "SBC A, H", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.H));
  });
  cpu->oMap[0x9D] = new Opcode(0x9D, "SBC A, L", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.L));
  });
  cpu->oMap[0x9E] = new Opcode(0x9E, "SBC A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SBC(a16);
  });
  cpu->oMap[0x9F] = new Opcode(0x9F, "SBC A, A", 1, 1, [&]() {
    cpu->SBC(&(cpu->reg.A));
  });

  // A0 - AF
  cpu->oMap[0xA0] = new Opcode(0xA0, "AND A, B", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.B));
  });
  cpu->oMap[0xA1] = new Opcode(0xA1, "AND A, C", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.C));
  });
  cpu->oMap[0xA2] = new Opcode(0xA2, "AND A, D", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.D));
  });
  cpu->oMap[0xA3] = new Opcode(0xA3, "AND A, E", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.E));
  });
  cpu->oMap[0xA4] = new Opcode(0xA4, "AND A, H", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.H));
  });
  cpu->oMap[0xA5] = new Opcode(0xA5, "AND A, L", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.L));
  });
  cpu->oMap[0xA6] = new Opcode(0xA6, "AND A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->AND(a16);
  });
  cpu->oMap[0xA7] = new Opcode(0xA7, "AND A, A", 1, 1, [&]() {
    cpu->AND(&(cpu->reg.A));
  });
  cpu->oMap[0xA8] = new Opcode(0xA8, "XOR A, B", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.B));
  });
  cpu->oMap[0xA9] = new Opcode(0xA9, "XOR A, C", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.C));
  });
  cpu->oMap[0xAA] = new Opcode(0xAA, "XOR A, D", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.D));
  });
  cpu->oMap[0xAB] = new Opcode(0xAB, "XOR A, E", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.E));
  });
  cpu->oMap[0xAC] = new Opcode(0xAC, "XOR A, H", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.H));
  });
  cpu->oMap[0xAD] = new Opcode(0xAD, "XOR A, L", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.L));
  });
  cpu->oMap[0xAE] = new Opcode(0xAE, "XOR A, (HL)", 2, 1, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->XOR(a16);
  });
  cpu->oMap[0xAF] = new Opcode(0xAF, "XOR A, A", 1, 1, [&]() {
    cpu->XOR(&(cpu->reg.A));
  });

  // B0 - BF

  // C0 - CF
  cpu->oMap[0xC0] = new Opcode(0xC0, "RET NZ", 2, 1, [&]() {
    cpu->RET(ConditionCode::NZ);
  });
  cpu->oMap[0xC1] = new Opcode(0xC1, "POP BC", 3, 1, [&]() {
    cpu->POP(&(cpu->reg.B), &(cpu->reg.C));
  });
  cpu->oMap[0xC2] = new Opcode(0xC2, "JP NZ, u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->JP(ConditionCode::NZ, u16);
  });
  cpu->oMap[0xC3] = new Opcode(0xC3, "JP u16", 4, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->JP(u16);
  });
  cpu->oMap[0xC4] = new Opcode(0xC4, "CALL NZ, u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->CALL(ConditionCode::NZ, u16);
  });
  cpu->oMap[0xC5] = new Opcode(0xC5, "PUSH BC", 4, 1, [&]() {
    cpu->PUSH(&(cpu->reg.B), &(cpu->reg.C));
  });
  cpu->oMap[0xC6] = new Opcode(0xC6, "ADD A, u8", 2, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->ADD(u8);
  });
  cpu->oMap[0xC7] = new Opcode(0xC7, "RST 00h", 4, 1, [&]() {
    cpu->RST(0x00);
  });
  cpu->oMap[0xC8] = new Opcode(0xC8, "RET Z", 2, 1, [&]() {
    cpu->RET(ConditionCode::Z);
  });
  cpu->oMap[0xC9] = new Opcode(0xC9, "RET", 4, 1, [&]() {
    cpu->RET();
  });
  cpu->oMap[0xCA] = new Opcode(0xCA, "JP Z, u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->JP(ConditionCode::Z, u16);
  });
  cpu->oMap[0xCC] = new Opcode(0xCC, "CALL Z, u16", 3, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->CALL(ConditionCode::Z, u16);
  });
  cpu->oMap[0xCD] = new Opcode(0xCD, "CALL u16", 6, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->CALL(u16);
  });
  cpu->oMap[0xCE] = new Opcode(0xCE, "ADC A, u8", 2, 3, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->ADC(u8);
  });
  cpu->oMap[0xCF] = new Opcode(0xCF, "RST 08h", 4, 1, [&]() {
    cpu->RST(0x08);
  });

  // D0 - DF

  // E0 - EF
  cpu->oMap[0xE0] = new Opcode(0xE0, "LD (FF00+u8), A", 3, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->LD(0xFF00 + u8);
  });
  cpu->oMap[0xE1] = new Opcode(0xE1, "POP HL", 3, 1, [&]() {
    cpu->POP(&(cpu->reg.H), &(cpu->reg.L));
  });
  cpu->oMap[0xE2] = new Opcode(0xE2, "LD (FF00+C), A", 2, 1, [&]() {
    cpu->LDHCA();
  });
  cpu->oMap[0xE5] = new Opcode(0xE5, "PUSH HL", 4, 1, [&]() {
    cpu->PUSH(&(cpu->reg.H), &(cpu->reg.L));
  });
  cpu->oMap[0xE6] = new Opcode(0xE6, "AND A, u8", 2, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->AND(u8);
  });
  cpu->oMap[0xE7] = new Opcode(0xE7, "RST 20h", 4, 1, [&]() {
    cpu->RST(0x20);
  });
  cpu->oMap[0xE8] = new Opcode(0xE8, "ADD SP, e8", 4, 2, [&]() {
    int8_t e8 = cpu->memory.read(cpu->PC + 1);
    cpu->ADDSP(e8);
  });
  cpu->oMap[0xE9] = new Opcode(0xE9, "JP HL", 1, 1, [&]() {
    uint16_t HL = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->JP(HL);
  });
  cpu->oMap[0xEA] = new Opcode(0xEA, "LD (u16), A", 4, 3, [&]() {
    uint16_t u16 = (cpu->memory.read(cpu->PC + 2) << 8) | cpu->memory.read(cpu->PC + 1);
    cpu->LD(u16);
  });
  cpu->oMap[0xEE] = new Opcode(0xEE, "XOR A, u8", 2, 2, [&]() {
    uint8_t u8 = cpu->memory.read(cpu->PC + 1);
    cpu->XOR(u8);
  });
  cpu->oMap[0xEF] = new Opcode(0xEF, "RST 28h", 4, 1, [&]() {
    cpu->RST(0x28);
  });
}

// TODO:
void CPU::initPrefixed(CPU* cpu) {
  // 00 - 0F
  cpu->pMap[0x00] = new Opcode(0x00, "RLC B", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.B));
  });
  cpu->pMap[0x01] = new Opcode(0x01, "RLC C", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.C));
  });
  cpu->pMap[0x02] = new Opcode(0x02, "RLC D", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.D));
  });
  cpu->pMap[0x03] = new Opcode(0x03, "RLC E", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.E));
  });
  cpu->pMap[0x04] = new Opcode(0x04, "RLC H", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.H));
  });
  cpu->pMap[0x05] = new Opcode(0x05, "RLC L", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.L));
  });
  cpu->pMap[0x06] = new Opcode(0x06, "RLC (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->RLC(a16);
  });
  cpu->pMap[0x07] = new Opcode(0x07, "RLC A", 2, 2, [&]() {
    cpu->RLC(&(cpu->reg.A));
  });
  cpu->pMap[0x08] = new Opcode(0x08, "RRC B", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.B));
  });
  cpu->pMap[0x09] = new Opcode(0x09, "RRC C", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.C));
  });
  cpu->pMap[0x0A] = new Opcode(0x0A, "RRC D", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.D));
  });
  cpu->pMap[0x0B] = new Opcode(0x0B, "RRC E", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.E));
  });
  cpu->pMap[0x0C] = new Opcode(0x0C, "RRC H", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.H));
  });
  cpu->pMap[0x0D] = new Opcode(0x0D, "RRC L", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.L));
  });
  cpu->pMap[0x0E] = new Opcode(0x0E, "RRC (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->RRC(a16);
  });
  cpu->pMap[0x0F] = new Opcode(0x0F, "RRC A", 2, 2, [&]() {
    cpu->RRC(&(cpu->reg.A));
  });

  // 10 - 1F
  
  // 20 - 2F
  cpu->pMap[0x20] = new Opcode(0x20, "SLA B", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.B));
  });
  cpu->pMap[0x21] = new Opcode(0x21, "SLA C", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.C));
  });
  cpu->pMap[0x22] = new Opcode(0x22, "SLA D", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.D));
  });
  cpu->pMap[0x23] = new Opcode(0x23, "SLA E", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.E));
  });
  cpu->pMap[0x24] = new Opcode(0x24, "SLA H", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.H));
  });
  cpu->pMap[0x25] = new Opcode(0x25, "SLA L", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.L));
  });
  cpu->pMap[0x26] = new Opcode(0x26, "SLA (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SLA(a16);
  });
  cpu->pMap[0x27] = new Opcode(0x27, "SLA A", 2, 2, [&]() {
    cpu->SLA(&(cpu->reg.A));
  });
  cpu->pMap[0x28] = new Opcode(0x28, "SRA B", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.B));
  });
  cpu->pMap[0x29] = new Opcode(0x29, "SRA C", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.C));
  });
  cpu->pMap[0x2A] = new Opcode(0x2A, "SRA D", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.D));
  });
  cpu->pMap[0x2B] = new Opcode(0x2B, "SRA E", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.E));
  });
  cpu->pMap[0x2C] = new Opcode(0x2C, "SRA H", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.H));
  });
  cpu->pMap[0x2D] = new Opcode(0x2D, "SRA L", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.L));
  });
  cpu->pMap[0x2E] = new Opcode(0x2E, "SRA (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SRA(a16);
  });
  cpu->pMap[0x2F] = new Opcode(0x2F, "SRA A", 2, 2, [&]() {
    cpu->SRA(&(cpu->reg.A));
  });

  // 30 - 3F

  // 40 - 4F
  cpu->pMap[0x40] = new Opcode(0x40, "BIT 0, B", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.B));
  });
  cpu->pMap[0x41] = new Opcode(0x41, "BIT 0, C", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.C));
  });
  cpu->pMap[0x42] = new Opcode(0x42, "BIT 0, D", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.D));
  });
  cpu->pMap[0x43] = new Opcode(0x43, "BIT 0, E", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.E));
  });
  cpu->pMap[0x44] = new Opcode(0x44, "BIT 0, H", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.H));
  });
  cpu->pMap[0x45] = new Opcode(0x45, "BIT 0, L", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.L));
  });
  cpu->pMap[0x46] = new Opcode(0x46, "BIT 0, (HL)", 3, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->BIT(0, a16);
  });
  cpu->pMap[0x47] = new Opcode(0x47, "BIT 0, A", 2, 2, [&]() {
    cpu->BIT(0, &(cpu->reg.A));
  });
  cpu->pMap[0x48] = new Opcode(0x48, "BIT 1, B", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.B));
  });
  cpu->pMap[0x49] = new Opcode(0x49, "BIT 1, C", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.C));
  });
  cpu->pMap[0x4A] = new Opcode(0x4A, "BIT 1, D", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.D));
  });
  cpu->pMap[0x4B] = new Opcode(0x4B, "BIT 1, E", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.E));
  });
  cpu->pMap[0x4C] = new Opcode(0x4C, "BIT 1, H", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.H));
  });
  cpu->pMap[0x4D] = new Opcode(0x4D, "BIT 1, L", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.L));
  });
  cpu->pMap[0x4E] = new Opcode(0x4E, "BIT 1, (HL)", 3, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->BIT(1, a16);
  });
  cpu->pMap[0x4F] = new Opcode(0x4F, "BIT 1, A", 2, 2, [&]() {
    cpu->BIT(1, &(cpu->reg.A));
  });

  // 50 - 5F

  
  // 60 - 6F
  cpu->pMap[0x60] = new Opcode(0x60, "BIT 4, B", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.B));
  });
  cpu->pMap[0x61] = new Opcode(0x61, "BIT 4, C", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.C));
  });
  cpu->pMap[0x62] = new Opcode(0x62, "BIT 4, D", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.D));
  });
  cpu->pMap[0x63] = new Opcode(0x63, "BIT 4, E", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.E));
  });
  cpu->pMap[0x64] = new Opcode(0x64, "BIT 4, H", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.H));
  });
  cpu->pMap[0x65] = new Opcode(0x65, "BIT 4, L", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.L));
  });
  cpu->pMap[0x66] = new Opcode(0x66, "BIT 4, (HL)", 3, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->BIT(4, a16);
  });
  cpu->pMap[0x67] = new Opcode(0x67, "BIT 4, A", 2, 2, [&]() {
    cpu->BIT(4, &(cpu->reg.A));
  });
  cpu->pMap[0x68] = new Opcode(0x68, "BIT 5, B", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.B));
  });
  cpu->pMap[0x69] = new Opcode(0x69, "BIT 5, C", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.C));
  });
  cpu->pMap[0x6A] = new Opcode(0x6A, "BIT 5, D", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.D));
  });
  cpu->pMap[0x6B] = new Opcode(0x6B, "BIT 5, E", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.E));
  });
  cpu->pMap[0x6C] = new Opcode(0x6C, "BIT 5, H", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.H));
  });
  cpu->pMap[0x6D] = new Opcode(0x6D, "BIT 5, L", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.L));
  });
  cpu->pMap[0x6E] = new Opcode(0x6E, "BIT 5, (HL)", 3, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->BIT(5, a16);
  });
  cpu->pMap[0x6F] = new Opcode(0x6F, "BIT 5, A", 2, 2, [&]() {
    cpu->BIT(5, &(cpu->reg.A));
  });

  // 70 - 7F
  
  // 80 - 8F
  cpu->pMap[0x80] = new Opcode(0x80, "RES 0, B", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.B));
  });
  cpu->pMap[0x81] = new Opcode(0x81, "RES 0, C", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.C));
  });
  cpu->pMap[0x82] = new Opcode(0x82, "RES 0, D", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.D));
  });
  cpu->pMap[0x83] = new Opcode(0x83, "RES 0, E", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.E));
  });
  cpu->pMap[0x84] = new Opcode(0x84, "RES 0, H", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.H));
  });
  cpu->pMap[0x85] = new Opcode(0x85, "RES 0, L", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.L));
  });
  cpu->pMap[0x86] = new Opcode(0x86, "RES 0, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->RES(0, a16);
  });
  cpu->pMap[0x87] = new Opcode(0x87, "RES 0, A", 2, 2, [&]() {
    cpu->RES(0, &(cpu->reg.A));
  });
  cpu->pMap[0x88] = new Opcode(0x88, "RES 1, B", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.B));
  });
  cpu->pMap[0x89] = new Opcode(0x89, "RES 1, C", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.C));
  });
  cpu->pMap[0x8A] = new Opcode(0x8A, "RES 1, D", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.D));
  });
  cpu->pMap[0x8B] = new Opcode(0x8B, "RES 1, E", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.E));
  });
  cpu->pMap[0x8C] = new Opcode(0x8C, "RES 1, H", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.H));
  });
  cpu->pMap[0x8D] = new Opcode(0x8D, "RES 1, L", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.L));
  });
  cpu->pMap[0x8E] = new Opcode(0x8E, "RES 1, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->RES(1, a16);
  });
  cpu->pMap[0x8F] = new Opcode(0x8F, "RES 1, A", 2, 2, [&]() {
    cpu->RES(1, &(cpu->reg.A));
  });

  // 90 - 9F

  // A0 - AF
  cpu->pMap[0xA0] = new Opcode(0xA0, "RES 4, B", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.B));
  });
  cpu->pMap[0xA1] = new Opcode(0xA1, "RES 4, C", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.C));
  });
  cpu->pMap[0xA2] = new Opcode(0xA2, "RES 4, D", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.D));
  });
  cpu->pMap[0xA3] = new Opcode(0xA3, "RES 4, E", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.E));
  });
  cpu->pMap[0xA4] = new Opcode(0xA4, "RES 4, H", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.H));
  });
  cpu->pMap[0xA5] = new Opcode(0xA5, "RES 4, L", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.L));
  });
  cpu->pMap[0xA6] = new Opcode(0xA6, "RES 4, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->RES(4, a16);
  });
  cpu->pMap[0xA7] = new Opcode(0xA7, "RES 4, A", 2, 2, [&]() {
    cpu->RES(4, &(cpu->reg.A));
  });
  cpu->pMap[0xA8] = new Opcode(0xA8, "RES 5, B", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.B));
  });
  cpu->pMap[0xA9] = new Opcode(0xA9, "RES 5, C", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.C));
  });
  cpu->pMap[0xAA] = new Opcode(0xAA, "RES 5, D", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.D));
  });
  cpu->pMap[0xAB] = new Opcode(0xAB, "RES 5, E", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.E));
  });
  cpu->pMap[0xAC] = new Opcode(0xAC, "RES 5, H", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.H));
  });
  cpu->pMap[0xAD] = new Opcode(0xAD, "RES 5, L", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.L));
  });
  cpu->pMap[0xAE] = new Opcode(0xAE, "RES 5, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->RES(5, a16);
  });
  cpu->pMap[0xAF] = new Opcode(0xAF, "RES 5, A", 2, 2, [&]() {
    cpu->RES(5, &(cpu->reg.A));
  });

  // B0 - BF

  // C0 - CF
  cpu->pMap[0xC0] = new Opcode(0xC0, "SET 0, B", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.B));
  });
  cpu->pMap[0xC1] = new Opcode(0xC1, "SET 0, C", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.C));
  });
  cpu->pMap[0xC2] = new Opcode(0xC2, "SET 0, D", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.D));
  });
  cpu->pMap[0xC3] = new Opcode(0xC3, "SET 0, E", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.E));
  });
  cpu->pMap[0xC4] = new Opcode(0xC4, "SET 0, H", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.H));
  });
  cpu->pMap[0xC5] = new Opcode(0xC5, "SET 0, L", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.L));
  });
  cpu->pMap[0xC6] = new Opcode(0xC6, "SET 0, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SET(0, a16);
  });
  cpu->pMap[0xC7] = new Opcode(0xC7, "SET 0, A", 2, 2, [&]() {
    cpu->SET(0, &(cpu->reg.A));
  });
  cpu->pMap[0xC8] = new Opcode(0xC8, "SET 1, B", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.B));
  });
  cpu->pMap[0xC9] = new Opcode(0xC9, "SET 1, C", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.C));
  });
  cpu->pMap[0xCA] = new Opcode(0xCA, "SET 1, D", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.D));
  });
  cpu->pMap[0xCB] = new Opcode(0xCB, "SET 1, E", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.E));
  });
  cpu->pMap[0xCC] = new Opcode(0xCC, "SET 1, H", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.H));
  });
  cpu->pMap[0xCD] = new Opcode(0xCD, "SET 1, L", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.L));
  });
  cpu->pMap[0xCE] = new Opcode(0xCE, "SET 1, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SET(1, a16);
  });
  cpu->pMap[0xCF] = new Opcode(0xCF, "SET 1, A", 2, 2, [&]() {
    cpu->SET(1, &(cpu->reg.A));
  });

  // D0 - DF

  // E0 - EF
  cpu->pMap[0xE0] = new Opcode(0xE0, "SET 4, B", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.B));
  });
  cpu->pMap[0xE1] = new Opcode(0xE1, "SET 4, C", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.C));
  });
  cpu->pMap[0xE2] = new Opcode(0xE2, "SET 4, D", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.D));
  });
  cpu->pMap[0xE3] = new Opcode(0xE3, "SET 4, E", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.E));
  });
  cpu->pMap[0xE4] = new Opcode(0xE4, "SET 4, H", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.H));
  });
  cpu->pMap[0xE5] = new Opcode(0xE5, "SET 4, L", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.L));
  });
  cpu->pMap[0xE6] = new Opcode(0xE6, "SET 4, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SET(4, a16);
  });
  cpu->pMap[0xE7] = new Opcode(0xE7, "SET 4, A", 2, 2, [&]() {
    cpu->SET(4, &(cpu->reg.A));
  });
  cpu->pMap[0xE8] = new Opcode(0xE8, "SET 5, B", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.B));
  });
  cpu->pMap[0xE9] = new Opcode(0xE9, "SET 5, C", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.C));
  });
  cpu->pMap[0xEA] = new Opcode(0xEA, "SET 5, D", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.D));
  });
  cpu->pMap[0xEB] = new Opcode(0xEB, "SET 5, E", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.E));
  });
  cpu->pMap[0xEC] = new Opcode(0xEC, "SET 5, H", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.H));
  });
  cpu->pMap[0xED] = new Opcode(0xED, "SET 5, L", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.L));
  });
  cpu->pMap[0xEE] = new Opcode(0xEE, "SET 5, (HL)", 4, 2, [&]() {
    uint16_t a16 = (cpu->reg.H << 8) | cpu->reg.L;
    cpu->SET(5, a16);
  });
  cpu->pMap[0xEF] = new Opcode(0xEF, "SET 5, A", 2, 2, [&]() {
    cpu->SET(5, &(cpu->reg.A));
  });

  
  // F0 - FF
  
  
}
