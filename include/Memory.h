#pragma  once
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

class Memory {
private:
    uint16_t memory[0xFFFF];
    uint8_t cartType;
    std::stringstream disassembledROM;
    void dumpROM(std::string ROMPath, std::ostream &out);
public:
    Memory(std::string ROMPath);
    uint16_t read(uint16_t address);
    void write(uint16_t address, uint16_t value);
};
