#include "cpu.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) 
{
  return cpu->ram[address];
}
void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) 
{
  cpu->ram[address] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

void cpu_load(struct cpu *cpu, char *argv[])
{
  // file pointer
  FILE *fp;
  int address = 0;
  char line[1024];

  fp = fopen(argv[1], "r");
  if(fp == NULL) 
  {
    fprintf(stderr, "** Error! Could not open this program.**\n");
    exit(1);
  }

while (fgets(line, sizeof(line), fp) != NULL) { // Loop until fgets is at the end of the file
    char *endptr;
    unsigned char value = strtoul(line, &endptr, 2); // Cast line to binary until value is captured
    
    if (endptr == line) {
      continue;
    }

    cpu_ram_write(cpu, address++, value); // Write the value to RAM address
  }

    fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      cpu->reg[regA] *= cpu->reg[regB];
      break;

    case ALU_ADD:
      cpu->reg[regA] += cpu->reg[regB];
      break;

    default:
      printf("** Error! Looks like there was no instruciton for ALU provided. **\n");
      break;
  }
}

void cpu_jump(struct cpu *cpu, unsigned char address){
  cpu->PC = cpu->reg[address];
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu) // Implement the core of `cpu_run()`
{
  int running = 1; // True until we get a HLT instruction
  // int inc;

  while (running) {
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->PC); // Read instructions from RAM
    // printf("** The value of the current instruction: %u **\n", IR);
    
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1); // Read additional operands 
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2); // Read additional operands
    // printf("hi\n");

    int number_of_operands = (IR >> 4) & 1;
    // int number_of_operands = (IR >> 6) + 1;
    // printf("%d \n", number_of_operands);
    // printf("IR = %d call = %d \n", IR, CALL);
    // inc = 1;
    switch(IR){
      case LDI: // Load "immediate", store a value in a register, or "set this register to this value
        cpu->reg[operandA] = operandB;
        break;

      case PRN:
        // Prints the numeric value stored in the register operandA (prints register)
        printf("** The numeric value stored in the register operandA: %d **\n", cpu->reg[operandA]);
        break;

      case MUL:
        // Call the ALU to execute MUL instruction
        alu(cpu, ALU_MUL, operandA, operandB);
        break;

      case ADD:
        alu(cpu, ALU_ADD, operandA, operandB);
        break;

      case PUSH:
        cpu->sp--;
        cpu_ram_write(cpu, cpu->sp, cpu->reg[operandA]);
        break;

      case POP:
        if(cpu->sp == 244)
        fprintf(stderr, "** Error! You ca not pop off an empty stack! **\n");
        cpu->reg[operandA] = cpu_ram_read(cpu, cpu->sp++);
        break;

      // case PUSH:
      // cpu->reg[cpu->sp]--;
      // cpu->ram[cpu->reg[cpu->sp]] = cpu->reg[operandA];
      // break;

      // case POP:
      //   cpu->reg[operandA] = cpu->ram[cpu->reg[cpu->sp]];
      //   cpu->reg[cpu->sp]++;
      //   break;

      case CALL:
        cpu->sp--;
        cpu_ram_write(cpu, cpu->sp, (cpu->PC + 2));
        cpu_jump(cpu, operandA);
        break;

      case RET:
        cpu->PC = cpu_ram_read(cpu, cpu->sp++);
        break;

      // case CALL:
      //   inc = 0;
      //   cpu->sp--;
      //   cpu->sp = cpu->PC + number_of_operands;
      //   cpu->PC = cpu->reg[operandA];
      //   // printf("cpu->PC = %d\n", cpu->PC);
      //   break;

      // case RET:
      //   inc = 0;
      //   cpu->PC = cpu->sp;
      //   cpu->reg[cpu->sp]++;
      //   inc = 0;
      //   break;

//       // case 0b01010000:
//       //   
//       //   cpu->sp--;
//       //   cpu_ram_write(cpu, cpu->sp, cpu->PC + number_of_operands);
//       //   break;

      case HLT:
        running = 0; // Halt. (False. Was true above.) Halt the CPU.
        break;

      default:
        printf("** Error! Unknown instruction at %02x: %02x **\n", cpu->PC, IR);
        exit(2); // Exit the emulator.
    }

//     if (inc) {
//       cpu->PC += number_of_operands; 
//     }

    if (!number_of_operands) {
      cpu->PC += ((IR >> 6) & 0x3) + 1;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // Zeroing out the PC, registers and ram
  cpu->sp = 244;
  cpu->fl = 0;
  cpu->PC = 0;
  memset(cpu->reg, 0, 8);
  memset(cpu->ram, 0, 256);
}

