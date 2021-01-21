#pragma  once
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

class CPU;    // Forward Declaration
class Memory {
private:
    uint8_t memory[0xFFFF] = {};
    uint8_t cartType;
    std::vector<uint8_t> disassembledROM;
    void dumpROM(std::string ROMPath);

protected:
    friend class CPU;
    uint8_t *LCDMode;       // Points to PPU's LCD Mode

public:
    Memory(std::string ROMPath);
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    void dump(std::ostream &out);
};
