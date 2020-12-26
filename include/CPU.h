#pragma once
#include <stdint.h>
#include <string>
#include <unordered_map>

#include "Opcode.h"
#include "Memory.h"

// Pre-defined Macros
#define TOTAL_FRAME_CYCLES 17556

class CPU {
private:
    std::unordered_map<std::string, Opcode> opcodeMap;
    uint8_t reg[8];     // A,B,C,D,E,H,L
    uint16_t PC;
    uint16_t SP;
    Memory memory;
    // TODO: PPU
    int cyclesLeftInCurrentFrame;   // Total 17556
    
    void handleInterrupt();
    void executeInstructions(int cycles);
public:
    CPU(std::string ROMPath);
    void nextFrame();               // Runs 60 Iterations / Seconds until no more free cycles pre Frame
};
