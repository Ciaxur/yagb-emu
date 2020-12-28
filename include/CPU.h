#pragma once
#include <stdint.h>
#include <string>
#include <unordered_map>

#include "Opcode.h"
#include "Memory.h"

// Pre-defined Macros
#define TOTAL_FRAME_CYCLES 17556

struct Register {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;  // Flags in Bit Order Left to Right: ZERO NEG HALF-CARRY CARRY (ZNHC)
    uint8_t H;
    uint8_t L;
};

class CPU {
protected:
    // CPU Instruction model based on RGBDS v0.4.2 documentation
    // 8-bit Arithmetic and Logic Instructions
    void ADC(uint8_t *r8);        // ADC A, r8
    void ADC(uint16_t a16);       // ADC A, [HL]
    void ADC(uint8_t u8);         // ADC A, u8

    void ADD(uint8_t *r8);        // ADD A, r8
    void ADD(uint16_t a16);       // ADD A, [HL]
    void ADD(uint8_t u8);         // ADD A, u8

    void AND(uint8_t *r8);        // AND A, r8
    void AND(uint16_t a16);       // AND A, [HL]
    void AND(uint8_t u8);         // AND A, u8

    void CP(uint8_t *r8);         // CP A, r8
    void CP(uint16_t a16);        // CP A, [HL]
    void CP(uint8_t u8);          // CP A, u8

    void DEC(uint8_t *r8);        // DEC r8
    void DEC(uint16_t a16);       // DEC [HL]

    void INC(uint8_t *r8);        // INC r8
    void INC(uint16_t a16);       // INC [HL]

    void OR(uint8_t *r8);         // OR A, r8
    void OR(uint16_t a16);        // OR A, [HL]
    void OR(uint8_t u8);          // OR A, u8

    void SBC(uint8_t *r8);        // SBC A, r8
    void SBC(uint16_t a16);       // SBC A, [HL]
    void SBC(uint8_t u8);         // SBC A, u8

    void SUB(uint8_t *r8);        // SUB A, r8
    void SUB(uint16_t a16);       // SUB A, [HL]
    void SUB(uint8_t u8);         // SUB A, u8

    void XOR(uint8_t *r8);        // XOR A, r8
    void XOR(uint16_t a16);       // XOR A, [HL]
    void XOR(uint8_t u8);         // XOR A, u8

private:
    std::unordered_map<uint16_t, Opcode*> oMap; // Opcode Map
    std::unordered_map<uint16_t, Opcode*> pMap; // Prefix Map
    Register reg;
    bool IME;
    uint16_t PC;
    uint16_t SP;
    Memory memory;
    // TODO: PPU
    int cyclesLeftInCurrentFrame;   // Total 17556
    
    void handleInterrupt();
    void executeInstructions(int cycles);

    // Flag Methods
    void checkCarry(uint8_t prev, uint16_t after);
    void checkHalfCarry(uint8_t prev, uint8_t after);

    // Initializers
    static void initOpcodes(CPU* cpu);
    static void initPrefixed(CPU* cpu);
public:
    CPU(std::string ROMPath);
    ~CPU();
    void nextFrame();               // Runs 60 Iterations / Seconds until no more free cycles pre Frame
};
