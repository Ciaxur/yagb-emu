#pragma once
#include <unordered_map>
#include <string>
#include "./Opcode.h"

// TODO:
void initOpcodes(std::unordered_map<std::string, Opcode*> &map) {
  // 00 - 0F
  map["00"] = new Opcode (0x00, "NOP", 1, 1, [](void *arg) {});

  // 01 - 1F

  // 20 - 2F
}

// TODO:
void initPrefixed(std::unordered_map<std::string, Opcode*> &map) {}
