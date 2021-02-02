#pragma once
#include "CPU.h"

class PPU {
protected:
    friend class CPU;
    uint8_t LCDMode;
    unsigned long currentFrame;
    uint8_t LY;

private:
    Memory *memory;
    CPU *cpu;

public:
    PPU(CPU *cpu, Memory *memory);

    void execute();
};