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

    // Initializers
    static void initOpcodes(CPU* cpu);
    static void initPrefixed(CPU* cpu);
public:
    CPU(std::string ROMPath);
    ~CPU();
    void nextFrame();               // Runs 60 Iterations / Seconds until no more free cycles pre Frame
};
