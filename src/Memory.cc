#include "../include/Memory.h"

/**
 * Initalizes the Memory, populating it
 *  with the givem ROM Path
 * @param ROMPath The path of the ROM
 */
Memory::Memory(std::string ROMPath) {
  std::cout << "Initializing Memory...\n";
  dumpROM(ROMPath, disassembledROM);

  // TODO: Populate Memory
  // TODO: Intitial Values
}

/**
 * Dumps the ROM to given Output Stream from
 *  the given ROM Path
 * @param ROMPath Path to the ROM that will be loaded
 * @param out Address of the Output Stream
 */
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

// TODO:
uint16_t Memory::read(uint16_t address) {}
void Memory::write(uint16_t address, uint16_t value) {}