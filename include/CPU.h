#pragma once
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <deque>

#include "Opcode.h"
#include "Memory.h"

// Pre-defined Macros
#define TOTAL_LINE_CYCLES 114
#define TOTAL_INSTR_PER_FRAME 17556

struct Register {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;  // Flags in Bit Order (Bit 7-4) Left to Right: ZERO NEG HALF-CARRY CARRY (ZNHC)
    uint8_t H;
    uint8_t L;
};

enum ConditionCode { Z, NZ, C, NC };

class PPU;    // Forward-Declaration
class CPU {
protected:
    // CPU Instruction model based on RGBDS v0.4.2 documentation
    // 8-bit Arithmetic and Logic Instructions
    void ADC(uint8_t *r8);                // ADC A, r8
    void ADC(uint16_t a16);               // ADC A, [HL]
    void ADC(uint8_t u8);                 // ADC A, u8

    void ADD(uint8_t *r8);                // ADD A, r8
    void ADD(uint16_t a16);               // ADD A, [HL]
    void ADD(uint8_t u8);                 // ADD A, u8

    void AND(uint8_t *r8);                // AND A, r8
    void AND(uint16_t a16);               // AND A, [HL]
    void AND(uint8_t u8);                 // AND A, u8

    void CP(uint8_t *r8);                 // CP A, r8
    void CP(uint16_t a16);                // CP A, [HL]
    void CP(uint8_t u8);                  // CP A, u8

    void DEC(uint8_t *r8);                // DEC r8
    void DEC(uint16_t a16);               // DEC [HL]

    void INC(uint8_t *r8);                // INC r8
    void INC(uint16_t a16);               // INC [HL]

    void OR(uint8_t *r8);                 // OR A, r8
    void OR(uint16_t a16);                // OR A, [HL]
    void OR(uint8_t u8);                  // OR A, u8

    void SBC(uint8_t *r8);                // SBC A, r8
    void SBC(uint16_t a16);               // SBC A, [HL]
    void SBC(uint8_t u8);                 // SBC A, u8

    void SUB(uint8_t *r8);                // SUB A, r8
    void SUB(uint16_t a16);               // SUB A, [HL]
    void SUB(uint8_t u8);                 // SUB A, u8

    void XOR(uint8_t *r8);                // XOR A, r8
    void XOR(uint16_t a16);               // XOR A, [HL]
    void XOR(uint8_t u8);                 // XOR A, u8

    // 16-bit Arithmetic Instructions
    void ADDHL(uint16_t r16);             // ADD HL, r16 | ADD HL, SP
    void DEC(uint8_t *ru, uint8_t *rl);   // DEC r16
    void INC(uint8_t *ru, uint8_t *rl);   // INC r16

    /* Bit Operations Instructions */
    void BIT(uint8_t u3, uint8_t *r8);    // BIT u3, r8
    void BIT(uint8_t u3, uint16_t a16);   // BIT u3, [HL]

    void RES(uint8_t u3, uint8_t *r8);    // RES u3, r8
    void RES(uint8_t u3, uint16_t a16);   // RES u3, [HL]

    void SET(uint8_t u3, uint8_t *r8);    // SET u3, r8
    void SET(uint8_t u3, uint16_t a16);   // SET u3, [HL]

    void SWAP(uint8_t *r8);               // SWAP r8
    void SWAP(uint16_t a16);              // SWAP [HL]

    /* Bit Shift Instructions */
    void RL(uint8_t *r8);                 // RL r8
    void RL(uint16_t a16);                // RL [HL]
    void RLA();                           // RLA

    void RLC(uint8_t *r8);                // RLC r8
    void RLC(uint16_t a16);               // RLC [HL]
    void RLCA();                          // RLCA

    void RR(uint8_t *r8);                 // RR r8
    void RR(uint16_t a16);                // RR [HL]
    void RRA();                           // RRA

    void RRC(uint8_t *r8);                // RRC r8
    void RRC(uint16_t a16);               // RRC [HL]
    void RRCA();                          // RRCA

    void SLA(uint8_t *r8);                // SLA r8
    void SLA(uint16_t a16);               // SLA [HL]

    void SRA(uint8_t *r8);                // SRA r8
    void SRA(uint16_t a16);               // SRA [HL]

    void SRL(uint8_t *r8);                // SRL r8
    void SRL(uint16_t a16);               // SRL [HL]

    /* Load Instructions */
    void LD(uint8_t *r1, uint8_t *r2);    // LD r8, r8
    void LD(uint8_t *r8, uint8_t u8);     // LD r8, u8
    void LD(uint8_t *ru, uint8_t *rl, uint16_t u16); // LD r16, u16

    void LD(uint16_t a16, uint8_t *r8);   // LD [HL], r8
    void LD(uint16_t a16, uint8_t u8);    // LD [HL], u8
    void LD(uint8_t *r8, uint16_t a16);   // LD r8, [HL]

    void LD(uint16_t a16);                // LD [r16], A | LD [u16], A

    void LDH(uint16_t a16);               // LDH [u16], A
    void LDHCA();                         // LDH [C], A

    void LDA(uint16_t a16);               // LD A, [r16] | LD A, [u16]

    void LDHA(uint16_t a16);              // LD A, [u16]
    void LDHAC();                         // LDH A, [C]

    void LDHLI();                         // LD [HLI], A
    void LDHLD();                         // LD [HLD], A

    void LDAHLI();                        // LD A, [HLI]
    void LDAHLD();                        // LD A, [HLD]

    /* Jumps and Subroutines */
    void CALL(uint16_t a16);              // CALL, u16
    void CALL(ConditionCode cc, uint16_t a16);  // CALL cc, u16

    void JP(uint16_t a16);                // JP u16
    void JPHL(uint16_t a16);              // JP HL
    void JP(ConditionCode cc, uint16_t a16);    // JP cc, u16

    void JR(int8_t e8);                   // JR e8
    void JR(ConditionCode cc, int8_t e8); // JR cc, e8

    void RET(ConditionCode cc);           // RET cc
    void RET();                           // RET
    void RETI();                          // RETI
    void RST(uint8_t vec);                // RST vec

    /* Stack Operations Instructions */
    void ADDSP(int8_t e8);                // ADD SP, e8

    void DECSP();                         // DEC SP
    void INCSP();                         // INC SP

    void LDSP(uint16_t u16);              // LD SP, u16 | LD SP, HL
    void LDSP_MEM(uint16_t a16);          // LD [u16], SP
    void LDHL(int8_t e8);                 // LD HL, SP+e8

    void POPAF();                         // POP AF
    void POP(uint16_t *r16);              // POP r16
    void POP(uint8_t *ru, uint8_t *rl);   // POP r16
    void PUSHAF();                        // PUSH AF
    void PUSH(uint16_t *r16);             // PUSH r16
    void PUSH(uint8_t *ru, uint8_t *rl);  // PUSH r16

    /* Miscellaneous Instructions */
    void CCF();                           // CCF
    void CPL();                           // CPL
    void DAA();                           // DAA

    void DI();                            // DI
    void EI();                            // EI

    void HALT();                          // HALT
    void SCF();                           // SCF

protected:
    friend class PPU;
    PPU *ppu;
    int lineCycles;     // Total 114
    int extraCycles;

public: // Public Variables
    std::deque<std::string> instructionStack;
    unsigned long totalInstructions = 0;
    unsigned long totalCycles = 0;

private:
    std::unordered_map<uint16_t, Opcode*> oMap; // Opcode Map
    std::unordered_map<uint16_t, Opcode*> pMap; // Prefix Map
    Register reg;
    bool IME;
    bool halted;
    bool running;
    uint16_t PC;
    uint16_t SP;
    Memory memory;
    std::ofstream cpuExecDump;

    void handleInterrupt();

    // Flag Methods
    void setZeroFlag(bool state);
    void setAddSubFlag(bool state);
    void setHalfCarryFlag(bool state);
    void setCarryFlag(bool state);

    // Flag Checks
    void checkHalfCarry(uint8_t prev, uint8_t after);
    void checkCarry(uint8_t prev, uint16_t after);

    // Initializers
    static void initOpcodes(CPU *cpu);
    static void initPrefixed(CPU *cpu);

public:
    CPU(std::string ROMPath);
    ~CPU();
    void nextFrame();               // Runs 60 Iterations / Seconds until no more free cycles pre Frame
    void executeInstructions(int cycles);
    void dump(std::ostream &out, bool isHeader = true, char endChar = '\n');   // Dumps Registers & CPU Dependant States
    const bool isRunning();
    void stop();
    const uint8_t *getMemory();
};
