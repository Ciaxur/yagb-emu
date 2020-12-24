#include "../include/Memory.h"

Memory::Memory(std::string ROMPath) {
  dumpROM(ROMPath, disassembledROM);
}

void Memory::dumpROM(std::string ROMPath, std::ostream &out) {
  uint8_t buffer[1000];
  int addr = 0;
  int n;
  int lineno = 0;
  std::ifstream infile;
  infile.open(ROMPath);

  // Check if file exists
  if (!infile) {
    std::cout << "ROM not found" << std::endl;
    return;
  }

  while (true) {
    infile.read((char *) buffer, 16);
    // Return buffer size up to 16
    n = infile.gcount();
    if (n <= 0) {
      break;
    }
    // Offset 16 bytes per line
    addr += 16;

    // Print line of n bytes
    for (int i = 0; i < 16; i++) {
      if (i + 1 <= n) {
        out << std::hex << std::setw(2) << std::setfill('0') << (int) buffer[i];
      }
      // Space each byte
      out << " ";
    }
    // New line after n bytes
    out << "\n";
    lineno += 16;

    // Break if end of file
    if (infile.eof()) {
      break;
    }
  }
}