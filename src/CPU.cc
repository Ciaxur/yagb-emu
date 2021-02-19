#include "../include/CPU.h"
#include "../include/OpcodeInit.hpp"
#include "../include/PPU.h"

/**
 * Initialize the CPU by constructing and populating
 *  Memory from the given ROM
 * @param ROMPath Path to the ROM
 */
CPU::CPU(std::string ROMPath): memory(ROMPath) {
  // Default Values
  cyclesLeft = 114;
  extraCycles = 0;
  halted = false;
  running = true;

  // Timer Cycles Initial State
  timerCycles.div = 0;
  timerCycles.tima = 0;

  // CPU Initial State
  IME = false;
  PC = 0x0100;
  SP = 0xFFFE;

  // Register Init
  //reg.A = 0x01; // Default for commercial roms
  reg.A = 0x11;   // Default for test roms
  reg.B = 0x00;
  reg.C = 0x13;
  reg.D = 0x00;
  reg.E = 0xD8;
  reg.F = 0xB0;
  reg.H = 0x01;
  reg.L = 0x4D;

  // Initialize the Opcode & Prefix Map
  this->initOpcodes(this);
  this->initPrefixed(this);

  ppu = new PPU(this, &this->memory);

  // Give memory access to LCD Mode
  this->memory.LCDMode = &(ppu->LCDMode);

  // Memory Power Up Sequence Init Values
  this->memory.memory[0xFF10] = 0x80; // NR10
  this->memory.memory[0xFF11] = 0xBF; // NR11
  this->memory.memory[0xFF12] = 0xF3; // NR12
  this->memory.memory[0xFF14] = 0xBF; // NR14
  this->memory.memory[0xFF16] = 0x3F; // NR21
  this->memory.memory[0xFF17] = 0x00; // NR22
  this->memory.memory[0xFF19] = 0xBF; // NR24
  this->memory.memory[0xFF1A] = 0x7F; // NR30
  this->memory.memory[0xFF1B] = 0xFF; // NR31
  this->memory.memory[0xFF1C] = 0x9F; // NR32
  this->memory.memory[0xFF1E] = 0xBF; // NR34
  this->memory.memory[0xFF20] = 0xFF; // NR41
  this->memory.memory[0xFF21] = 0x00; // NR42
  this->memory.memory[0xFF22] = 0x00; // NR43
  this->memory.memory[0xFF23] = 0xBF; // NR44
  this->memory.memory[0xFF24] = 0x77; // NR50
  this->memory.memory[0xFF25] = 0xF3; // NR51
  this->memory.memory[0xFF26] = 0xF1; // NR52 (Gameboy = 0xF1)
  this->memory.memory[0xFF40] = 0x91; // LCDC
  this->memory.memory[0xFF47] = 0xFC; // BGP
  this->memory.memory[0xFF48] = 0xFF; // OBP0
  this->memory.memory[0xFF49] = 0xFF; // OBP1
}

/**
 * Frees up memory used
 *  - Opcode Map Pointers
 */
CPU::~CPU() {
  // Free up Mapped Opcode Execute Methods
  for (auto key: this->oMap) {
    delete key.second;
  }
  for (auto key: this->pMap) {
    delete key.second;
  }
  delete this->ppu;
  cpuExecDump.close();
};

/**
 * Handles Ticking CPU + PPU States
 */
void CPU::tick() {
  if (!halted)
    ppu->execute();
  else
    handleInterrupt();
}

/**
 * Sets the Z Flag (Bit 7) to given State
 * @param state State of the Flag
 */
void CPU::setZeroFlag(bool state) {
  state ? this->reg.F |= 0x80 : this->reg.F &= 0x7F;
}

/**
 * Sets the N Flag (Bit 6) to given State
 * @param state State of the Flag
 */
void CPU::setAddSubFlag(bool state) {
  state ? this->reg.F |= 0x40 : this->reg.F &= 0xBF;
}

/**
 * Sets the H Flag (Bit 5) to given State
 * @param state State of the Flag
 */
void CPU::setHalfCarryFlag(bool state) {
  state ? this->reg.F |= 0x20 : this->reg.F &= 0xDF;
}

/**
 * Sets the C Flag (Bit 4) to given State
 * @param state State of the Flag
 */
void CPU::setCarryFlag(bool state) {
  state ? this->reg.F |= 0x10 : this->reg.F &= 0xEF;
}

/**
 * Sets Half-Carry flag if a half carry occurred for 8bit Value
 * @param prev The previous value
 * @param after Result of the previous value
 * @return Result of the Set (if needed)
 */
void CPU::checkHalfCarry(uint8_t prev, uint8_t after) { // Overflow from 3rd Bit
  this->reg.F &= 0xDF;                    // Unset H Flag
  if ((prev & 0x0F) != (after & 0x0F))    // LSB Change
    if ((prev & 0xF0) != (after & 0xF0))  // MSB Change
      this->reg.F |= 0x20;                // Set H Flag
}

/**
 * Sets Carry flag if a carry occurred for 8bit Value
 * @param prev The previous value
 * @param after Result of the previous value
 * @return Result of the Set (if needed)
 */
void CPU::checkCarry(uint8_t prev, uint16_t after, bool isSubOp) { // Overflow from 7th Bit
  this->reg.F &= 0xEF;                         // Unset C Flag

  if (isSubOp && prev > after)
    this->reg.F |= 0x10;

  else if (isSubOp && (prev & 0xFF) != (after & 0xFF))  // LSB Change
    if ((prev & 0xFF00) != (after & 0xFF00))            // MSB Change
      this->reg.F |= 0x10;                              // Set C Flag
}

/**
 * Dumps all CPU Dependant States ie. Registers
 * @param out Output stream to dump to
 */
void CPU::dump(std::ostream &out, bool isHeader, char endChar) {
  // Store Default Formatting
  std::ios init(nullptr);
  init.copyfmt(out);

  if (isHeader) out << "== REGISTERS ==\n";
  out << std::setfill('0') << std::uppercase << std::hex << "  A: " << std::setw(2) << (int)reg.A << endChar;
  out << std::uppercase << std::hex << "  B: " << std::setw(2) << (int)reg.B << endChar;
  out << std::uppercase << std::hex << "  C: " << std::setw(2) << (int)reg.C << endChar;
  out << std::uppercase << std::hex << "  D: " << std::setw(2) << (int)reg.D << endChar;
  out << std::uppercase << std::hex << "  E: " << std::setw(2) << (int)reg.E << endChar;
  out << std::uppercase << std::hex << "  F: " << std::setw(2) << (int)reg.F << endChar;
  out << std::uppercase << std::hex << "  H: " << std::setw(2) << (int)reg.H << endChar;
  out << std::uppercase << std::hex << "  L: " << std::setw(2) << (int)reg.L << endChar;
  out << std::uppercase << std::hex << "  HL: " << std::setw(4) << (int)((reg.H << 8) | reg.L) << endChar;
  out << std::uppercase << std::hex << "  SP: " << std::setw(4) << SP << endChar;
  out << std::uppercase << std::hex << "  PC: " << std::setw(4) << PC << endChar;

  if (isHeader) out << "\n== STATES ==\n";
  out << std::uppercase << std::hex << "  IME: " << IME << endChar;
  out << std::uppercase << std::hex << "  LY: " << (int)ppu->LY << endChar;
  out << std::uppercase << std::hex << "  LY[0xFF44]: " << (int)memory.memory[0xFF44] << endChar;
  out << std::uppercase << std::hex << "  LCDC [0xFF40]: " << (int)memory.memory[0xFF40] << endChar;
  out << std::uppercase << std::hex << "    " << std::bitset<8>(memory.memory[0xFF40]) << endChar << endChar;
  out << std::uppercase << std::hex << "  STAT [0xFF41]: " << (int)memory.memory[0xFF41] << endChar;
  out << std::uppercase << std::hex << "    " << std::bitset<8>(memory.memory[0xFF41]) << endChar << endChar;

  out << std::uppercase << std::hex << "  IE [0xFFFF]: " << (int)memory.memory[0xFFFF] << endChar;
  out << std::uppercase << std::hex << "    " << std::bitset<8>(memory.memory[0xFFFF]) << endChar << endChar;
  out << std::uppercase << std::hex << "  IF [0xFF0F]: " << (int)memory.memory[0xFF0F] << endChar;
  out << std::uppercase << std::hex << "    " << std::bitset<8>(memory.memory[0xFF0F]) << endChar << endChar;

  out << std::uppercase << std::dec << "  FRAME: " << ppu->currentFrame << endChar;
  out << std::uppercase << std::hex << "  HALTED: " << halted << endChar;
  out << std::uppercase << std::hex << "  RUNNING: " << running << endChar;

  if (isHeader) out << "\n== FLAGS ==\n";
  out << std::uppercase << std::hex << "  Z: " << ((reg.F & 0x80) >> 7) << endChar;
  out << std::uppercase << std::hex << "  N: " << ((reg.F & 0x40) >> 6) << endChar;
  out << std::uppercase << std::hex << "  H: " << ((reg.F & 0x20) >> 5) << endChar;
  out << std::uppercase << std::hex << "  C: " << ((reg.F & 0x10) >> 4) << endChar;

  // Revert Formatting Back
  out.copyfmt(init);
}

/**
 * @return State of running the CPU
 */
const bool CPU::isRunning() {
  return this->running;
}

/**
 * Handle CPU Instructions from PC! 🤠🤠🤠🤠
 * @param cycles Cycles the CPU is allowed to Run for
 */
void CPU::execute() {
  // Handle Pre-Execution Process
  if (!this->running) return;
  handleInterrupt();

  // Verify PC Validity
  if (PC < 0x0040 || this->PC > 0xFFFF || this->PC < 0x0000) {
    std::cout << "Something went wrong...\n";
    std::cout << "Invalid PC = " << this->PC << '\n';
    this->running = false;

    // CPU Dump
    std::cout << "Dumping CPU State to 'cpu_state.dump'\n";
    std::ofstream out("cpu_state.dump", std::ios::out);
    dump(out);
    out.close();

    return;
  }

  // Execute current Instruction
  // Get Opcode Value
  uint8_t currentOpcode = this->memory.read(this->PC);

  // Condition between Opcode & PREFIX Table
  Opcode *opcodeObj;
  if (currentOpcode!= 0xCB) {
    opcodeObj = oMap[currentOpcode];
  } else {
    opcodeObj = pMap[this->memory.read(this->PC + 1)];
  }

  // Keep track of Previous 10 Instructions
  std::ostringstream ss;
  ss << std::hex << std::uppercase;
  ss << PC << ": " << opcodeObj->label << " | ";
  ss << std::hex << std::uppercase
     << (int)memory.read(PC) << " "
     << (int)memory.read(PC + 2) << " " << (int)memory.read(PC + 1);
  instructionStack.push_back(ss.str());
  if (instructionStack.size() >= 20)
    instructionStack.pop_front();

  // Exec Opcode
  opcodeObj->exec();

  // Set new PC
  this->PC += opcodeObj->length;

  // Keep track of CPU's State
  uint8_t cyclesTaken = this->extraCycles + opcodeObj->machineCycles;

  // Decrement CyclesLeft & Additional Cycles taken by Opcode
  totalInstructions++;
  totalCycles += cyclesTaken;
  cyclesLeft -= cyclesTaken;
  this->extraCycles = 0;

  // Update Timers
  updateTimers(cyclesTaken);
}

/**
 * Handles (IME = 1) Requested Interrupt (IF) given the associated
 *  interrupt is Enabled (IE).
 */
void CPU::handleInterrupt() {
  if (this->IME) {
    std::cout << "CPU INTERRUPTED!\n";

    // Memory Registers Required
    uint8_t IE = this->memory.read(0xFFFF);
    uint8_t IF = this->memory.read(0xFF0F);
    uint8_t IH = (IE & IF) & 0x1F;

    // Least Significant bit gets highest priority
    if (IH & 0x01) {          // Bit0: V-Blank
      // Basically CALL without the offset
      this->PUSH(&PC);
      PC = 0x0040;

      // Consume CPU Cycles + 2 (internal timing NOPs)
      cyclesLeft -= 5;
      updateTimers(5);

      // Unset Handled Bit
      IF &= ~0x01;

      // Dispatch Handled
      IME = false;
    } else if (IH & 0x02) {   // Bit1: LCD STAT
      this->PUSH(&PC);
      PC = 0x0048;
      cyclesLeft -= 5;
      updateTimers(5);
      IF &= ~0x02;
      IME = false;
    } else if (IH & 0x04) {   // Bit2: Timer
      this->PUSH(&PC);
      PC = 0x0050;
      cyclesLeft -= 5;
      updateTimers(5);
      IF &= ~0x04;
      IME = false;
    } else if (IH & 0x08) {   // Bit3: Serial
      this->PUSH(&PC);
      PC = 0x0058;
      cyclesLeft -= 5;
      updateTimers(5);
      IF &= ~0x08;
      IME = false;
    } else if (IH & 0x10) {   // Bit4: Joypad
      this->PUSH(&PC);
      PC = 0x0060;
      cyclesLeft -= 5;
      updateTimers(5);
      IF &= ~0x10;
      IME = false;
    }

    // Update IF
    this->memory.write(0xFF0F, IF);
  }

  // Check IME Delayed Enable (EI)
  else if (delayed_IME) {
    delayed_IME = false;
    IME = true;
  }
}

/**
 * Stops the entire program
 */
void CPU::stop() {
  this->running = false;
}

/**
 * Returns a pointer to Memory
 * @returns Constant Pointer to Memory Object
 */
const uint8_t* CPU::getMemory() {
  return this->memory.memory;
}

/**
 * @return A Snapshot of the current CPU's State
 */
const CPU_State CPU::getCpuStateSnapshot() {
  return {
    reg,
    SP,
    PC,
    ppu->LY,
    IME,
    halted,
    running
  };
}

/**
 * @return Returns the PPU's Current Frame State
 */
const int CPU::getCurrentFrame() {
  return this->ppu->currentFrame;
}

/**
 * Updates all Timers based on the total passed cycles.
 * @param cyclesPassed Total Cycles executed by the CPU
 */
void CPU::updateTimers(uint8_t cyclesPassed) {
  // Keep track of Cycles passed for each of the Timers
  this->timerCycles.div += cyclesPassed;

  // Get TAC Configuration
  uint8_t TAC = this->memory.read(0xFF07);


  if (this->timerCycles.div >= 64) {
    uint8_t DIV = this->memory.read(0xFF04);
    memory.memory[0xFF04] = ++DIV;
    this->timerCycles.div -= 64;
  }



  // TAC-Enabled, Tick TIMA
  // TODO: Figure out what happens if TAC changes interval while TAC enabled.
  if (TAC & (1 << 2)) {
    this->timerCycles.tima += cyclesPassed;
    uint8_t TIMA_OLD = this->memory.read(0xFF05);
    uint8_t TIMA = TIMA_OLD;

    switch (TAC & 0x03) {
      case 0x00:
        if (timerCycles.tima >= 256) {
          TIMA++;
          timerCycles.tima -= 256;
        }
        break;
      case 0x01:
        if (timerCycles.tima >= 4) {
          TIMA++;
          timerCycles.tima -= 4;
        }
        break;
      case 0x10:
        if (timerCycles.tima >= 16) {
          TIMA++;
          timerCycles.tima -= 16;
        }
        break;
      case 0x11:
        if (timerCycles.tima >= 64) {
          TIMA++;
          timerCycles.tima -= 64;
        }
        break;
    }

    // CHECK IF OVERFLOW
    if (TIMA < TIMA_OLD) {
      // Request Timer Interrupt
      uint8_t IF = this->memory.read(0xFF0F);
      this->memory.write(0xFF0F, IF |= 0x04);

      // Set TIMA = TAC
      TIMA = this->memory.read(0xFF06);
    }


    this->memory.write(0xFF05, TIMA);
  }


}