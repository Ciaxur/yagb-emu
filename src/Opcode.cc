#include "../include/Opcode.h"

/**
 * Initializes an Opcode's details required to execute the
 *  instruction given the function logic that it executes
 * 
 * @param opcode The Opcode Hex Value (ex. 0x00)
 * @param label Associated Label for the Opcode (ex. NOP)
 * @param machineCycles Number of Cycles the Instruction takes to execute
 * @param length Length of the Entire Opcode, including Operands
 * @param exec Pointer to the Function Logic of the Instruction
 */
Opcode::Opcode(uint8_t opcode, std::string label, uint16_t machineCycles, uint16_t length, std::function<void(void*)> exec) {
    this->opcode = opcode;
    this->label = label;
    this->machineCycles = machineCycles;
    this->length = length;
    this->exec = exec;
}
