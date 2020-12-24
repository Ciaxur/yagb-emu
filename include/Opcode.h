#pragma once
#include <stdint.h>
#include <string>
#include <functional>

class Opcode {
private:
    uint8_t opcode;
    std::string label;
    uint16_t machineCycles;
    uint16_t length;
public:
    Opcode(uint8_t opcode, std::string label, uint16_t machineCycles, uint16_t length, std::function<void(void*)> exec);
    std::function<void(void*)> exec;
};
