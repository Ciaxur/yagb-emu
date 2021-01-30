#include "../include/Memory.h"
#include "CPU.h"

/**
 * Initalizes the Memory, populating it
 *  with the givem ROM Path
 * @param ROMPath The path of the ROM
 */
Memory::Memory(std::string ROMPath) {
  std::cout << "Dumping ROM...\n";
  dumpROM(ROMPath);

  // Populate Memory
  std::cout << "Populating Memory...\n";
  if (disassembledROM.size() >= 0x7FFF) {
    for (int i = 0; i <= 0x7FFF; i++) {
      memory[i] = disassembledROM[i];
    }
  } else {
    // TODO: Halt, bad dump
  }

  // TODO: Intitial Values
}


/**
 * Dumps the ROM to disassembled internal array
 *  given the given ROM Path
 * @param ROMPath Path to the ROM that will be loaded
 */
void Memory::dumpROM(std::string ROMPath) {
  std::ifstream infile;
  infile.open(ROMPath);

  // Check if file exists
  if (!infile) {
    std::cout << "ROM not found" << std::endl;
    return;
  }

  // Allocate Space
  disassembledROM.clear();
  disassembledROM.reserve(1024 * 32);

  uint8_t buffer[1];
  for (int i=0; !infile.eof(); i++) {
    infile.read((char *) buffer, 1);
    if (infile.gcount())
      disassembledROM.push_back(buffer[0]);
  }
  std::cout << "ROM Disassembled!\n";
}

/**
 * Dumps Memory to given Output Stream
 * @param out Output Stream
 */
void Memory::dump(std::ostream &out) {
  std::ios init(nullptr);
  init.copyfmt(out);
  out << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << 0 << ": ";

  int j = 0;
  for (int i = 0; i < 0xFFFF; i++) {
    if (j == 16) {
      j = 0;
      out << "\n" << std::setw(4) << i << ": ";
    }
    j++;
    out << std::setw(2) << (int)memory[i] << (j == 8 ? "\t\t" : " ");
  }
  out.copyfmt(init);
}

// TODO:
uint8_t Memory::read(uint16_t address) {
  //std::cout << "Accessing Address: " << address << std::endl;

  // TODO: OAM
  if (address >= 0x0000 && address < 0xFFFF) {
    return memory[address];
  }
  else {
      std::cout << "Memory.read [" << std::hex << address << std::dec << "]: YO OUT OF RANGE!\n";
      // TODO: Halt CPU Loop
  }
}

void Memory::write(uint16_t address, uint8_t value) {

  // TODO: MBC Switch
  if (address < 0x7FFF) {

  }

  // Output Serial Link
  else if (address == 0xFF02 && value == 0x81) {
    std::cout << "Serial Link Value: " << std::hex << (int)this->read(0xFF01) << '\n';
  }

  // VRAM Write
  else if (address >= 0x8000 && address <= 0x9FFF && *(this->LCDMode) != 3) {
    memory[address] = value;
  }

  // Reset DIV if writen to
  else if (address == 0xFF04) {
    memory[0xFF04] = 0;
  }

  // Prohibited Areas, NO.
  else if (!(address >= 0xE000 && address <= 0xFDFF) && !(address >= 0xFEA0 && address <= 0xFEFF)) {
    memory[address] = value;
  }

  else {
    // Writing out of range
    std::cout << "Memory.write [" << std::hex << address << std::dec << "]: INVALID RANGE!\n";
  }
}
