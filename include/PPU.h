#pragma once
#include "CPU.h"

class PPU {
protected:

private:
    Memory *memory;
    CPU *cpu;
    uint8_t LCDMode;
public:
    PPU(CPU *cpu, Memory *memory);

    void generateScanline(int LY);
};