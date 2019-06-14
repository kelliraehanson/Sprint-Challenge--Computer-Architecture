#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  int fl;
  unsigned int PC; // PC
  unsigned char reg[8]; // registers (array)
  unsigned char ram[256]; // ram (array)
  int sp;
} cpu;
// With 8 bits, our CPU has a total of 256 bytes of memory and can only compute values up to 255.
// The CPU could support 256 instructions, as well, but we won't need them.


// ALU operations
enum alu_op {
  ALU_MUL,
  ALU_ADD
};

// Instructions
#define ADD  0b10100000
#define HLT  0b00000001
#define LDI  0b10000010
#define PRN  0b01000111
#define MUL  0b10100010
#define POP  0b01000110
#define PUSH 0b01000101
#define CALL 0b01010000
#define RET  0b00010001

// TODO: more instructions here. These can be used in cpu_run().

// Function declarations
extern void cpu_load(struct cpu *cpu, char *argv[]);
// extern void cpu_load(struct cpu *cpu, char *fileName);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
