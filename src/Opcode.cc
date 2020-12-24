#include "../include/Opcode.h"

Opcode::Opcode(uint8_t opcode, std::string label, uint16_t machineCycles, uint16_t length, std::function<void(void*)> exec) {
    this->opcode = opcode;
    this->label = label;
    this->machineCycles = machineCycles;
    this->length = length;
    this->exec = exec;
}
