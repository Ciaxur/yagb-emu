## Disassembler
- Uses Little-Endian Byte Order
- Instruction `0xCB` Prefixes an Additional Table

## CPU
- 8 Bit Registers
- Prefix Includes 0xCB (2 Bytes Total Including 1Byte of 0xCB) = 2 Bytes
- Interrupts
  - Memory Registers

## Interrupt
- `Q1`: What happens to IE after the CPU handles the interrupt routine? (*Answered*)

## Timer
- 1 Machine Cycle = 4 Clock Cycles (Ticks)
  - `Example`: NOP is 4 Clock Cycles indicated by 4t (*Refer to Timing on Journey Doc*)

## PPU
- 