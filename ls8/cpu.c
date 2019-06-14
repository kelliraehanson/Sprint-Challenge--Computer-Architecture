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
      case LDI: // Load "immediate", store a value in a register, or "set this register to this value.
      // LDI register immediate.
      // Set the value of a register to an integer.
        cpu->reg[operandA] = operandB;
        break;

      case PRN: // PRN register
        // Prints the numeric value stored in the register operandA (prints register)
        // Print alpha character value stored in the given register.
        // Print to the console the ASCII character corresponding to the value in the register.
        printf("** The numeric value stored in the register operandA: %d **\n", cpu->reg[operandA]);
        break;

      case MUL: // MUL operandA operandB
        // Call the ALU to execute MUL instruction
        // Multiply the values in two registers together and store the result in operandA.
        alu(cpu, ALU_MUL, operandA, operandB);
        break;

      case ADD: // ADD operandA operandB
      // This is an instruction handled by the ALU.
      // Add the value in two registers and store the result in operandA.
        alu(cpu, ALU_ADD, operandA, operandB);
        break;

      case PUSH: // PUSH register
      // Push the value in the given register on the stack.
      // Decrement the SP.
      // Copy the value in the given register to the address pointed to by SP.
        cpu->sp--;
        cpu_ram_write(cpu, cpu->sp, cpu->reg[operandA]);
        break;

      case POP:// POP register
      // Pop the value at the top of the stack into the given register.
      // Copy the value from the address pointed to by SP to the given register. Increment SP.
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

      case CALL: // CALL register
        cpu->sp--;
        cpu_ram_write(cpu, cpu->sp, (cpu->PC + 2));
        cpu_jump(cpu, operandA);
        break;
    // Calls a subroutine (function) at the address stored in the register.
    // The address of the instruction directly after CALL is pushed onto the stack. 
    // This allows us to return to where we left off when the subroutine finishes executing.
    // The PC is set to the address stored in the given register. 
    // We jump to that location in RAM and execute the first instruction in the subroutine. 
    // The PC can move forward or backwards from its current location.

      case RET: // Return register
      // Return from subroutine.
      // Pop the value from the top of the stack and store it in the PC.
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

      case CMP: // Compare instruction 
      // CMP operandA operandB
        if(cpu->reg[operandA] == cpu->reg[operandB]) cpu->fl = 1;
        break;
    // Compare the values in two registers.
    // If they are equal, set the Equal E flag to 1, otherwise set it to 0.
    // If registerA is less than registerB, set the Less-than L flag to 1, otherwise set it to 0.
    // If registerA is greater than registerB, set the Greater-than G flag to 1, otherwise set it to 0.

      case JMP: // Jump register instruction 
      // Jump to the address stored in the given register.
      // Set the PC to the address stored in the given register.
        cpu_jump(cpu, operandA);
        number_of_operands = 1;
        break;

      case JEQ: // JEQ register
      // If equal flag is set (true), jump to the address stored in the given register.
      // JEQ = Jump if equal => another
        if(cpu->fl) cpu_jump(cpu, operandA);
        else cpu->PC = cpu->PC + 2; // Shorthand: else cpu->PC += 2;
        break;

      case JNE: // JNE register. Jump if condition is met
      // If E flag is clear (false, 0), jump to the address stored in the given register.
        if(!cpu->fl) cpu_jump(cpu, operandA);
        else cpu->PC = cpu->PC + 2; // Shorthand: else cpu->PC += 2;
        break;

      case HLT: // HLT
      // Halt the CPU (and exit the emulator).
        running = 0; // Halt. (False. Was true above.) Halt the CPU.
        break;

    // When you add two numbers with highest bit set, you'd end up with result 
    // with one bit longer that the original numbers. This new bit "goes" to carry. 
    // It's also used as borrow-flag in subtractions. 
    // Compare is the same as subtraction except that the result value is not stored.

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

