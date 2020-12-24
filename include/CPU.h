#pragma once
#include <stdint.h>
#include <string>
#include <unordered_map>

#include "Opcode.h"
#include "Memory.h"

class CPU {
private:
    std::unordered_map<std::string, Opcode> opcodeMap;
    uint8_t reg[8];     // A,B,C,D,E,H,L
    uint16_t PC;
    uint16_t SP;
    Memory memory;
    // PPU
    int cyclesLeftInCurrentFrame;   // Default 17556
    void handleInterrupt();
public:
    CPU(std::string ROMPath);
    void nextFrame();               // Runs 60 Iterations / Seconds until no more free cycles
    void executeInstruction(int cycles);
};

