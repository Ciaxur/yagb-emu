#pragma once
#include <stdint.h>
#include <string>
#include <functional>

class Opcode {
protected:
    uint8_t opcode;
    std::string label;
    uint16_t machineCycles;
    uint16_t length;

    friend class CPU;
public:
    Opcode(uint8_t opcode, std::string label, uint16_t machineCycles, uint16_t length, std::function<void()> exec);
    std::function<void()> exec;
    const std::string getLabel();
};
