#pragma once
#include "CPU.h"

class PPU {
protected:
    friend class CPU;
    uint8_t LCDMode;

private:
    Memory *memory;
    CPU *cpu;

public:
    PPU(CPU *cpu, Memory *memory);

    void generateScanline(int LY);
};