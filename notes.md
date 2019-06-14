What is the CPU and how does it work?

The computer does its primary work in a part of the machine we cannot see, a control center that converts data input to information output. This control center, called the central processing unit (CPU), is a highly complex, extensive set of electronic circuitry that executes stored program instructions.


Computer Architecture: CPU and Components

The Beginning:
    - Transistors, the most basic
    - Gates, mad of transistors
    - Digital Logic common operations preformed by gates
        - AND, OR, NOT, like you've seen in conditionals in code
        - XOR, NOR, NAND
    - Gates can be put together into far more complex structures
        - ALU
        - CPUs

RAM:
    - RAM stands for Random Access Memory.
    - Fast compared to hard drives (and even compared to SSDs)
    - Think of it like abig array of bytes that you can access by index, just like an array in your favorite programming language.
    - Each element in RAM can store on byte, an 8-bit number
    - Larget, mulit-byte values are stored in sequential addresses in RAM
    - The CPU communicates with RAM via the memory bus

CPU words:
    - Bytes of data are stored in RAM(memory)
    - Larger 64-bit (8-byte) numbers, stored sequentially in RAM, that the CPU can operate on at once are called words.
    - The exact number of bytes per wod depends on the architecture
        - 8 bytes for a 64-bit CPU
        - 4 bytes for a 32-bit CPU
        - 1 bytes for an 8-bit CPU

CPU Registers:
Refisters store words that can be accessed at ultra-high-speed
    - Think of them like variables that the CPU has at its disposal.
    - Similar to RAM, except stored directly on the CPU so they are much faster.
    - There are a limited number of them at your disposal, usually 8, 16, or 32, depending on the CPU.
    - They have fixed names, e.g. R0, R1 or EAX, EBX, etc. depending on the CPU.
    - Many CPUs can only perform math operations on registers which must be loaded from RAM first. (The x86 family can often perform math on registers quickly, or RAM  slowly.)

CPU Instructions:
    - Are also stored in RAM with other data.
    - Are actually just numbers.
    - Humans often use mnemonics to refer to the instruction in a human-readable way.
    - The CPU keeps track of the address of the currently-executing instruction in RAM and preforms different actions based on the instructoin found there.
    - The address of the currently-executing instrucion is held in a special register called the program counter (PC)
    - CPUs usually have a significant number of instructions, around 50-200

CPU Clock:
    - The clock in a modern CPU triggers a few billion times per second.
    - Clock cycle rate is measured in Hz, KHz, MHz, or GHz (billions of cycles per second)
    - Each instruction takes one or more clock cycles to execute.
    - The faster the clock, the more instructions can execute per second. 

Concurrency:
How the CPU does more than one thing at once.
    - Each hardware component can only do one thing at once.
    - Duplicate the hardware components!
    - Multi-core CPUs
    - Pipelining
    - Timesharing 

System Bus:
How data is passed from the CPU to RAM, and from the CPU to peripherals.
    - Address Bus: carries the address in RAM we're interested in, or the peripheral ID we're interested in. 
    - Data Bus: carries data to be transmitted to or from RAM or peripherals.
    - Control Bus: controls whether or not the CPU is talking to RAM or peripheral.
    - The size or width of the bus is typically the number of "bits" a computer is advertised having. A 63-bit CPU has a 64-bit wide data bus, and usually a 64-bit wide address bus. 

Caching:
    - Access to RAM is relative slow.
    - Access to Registers is fast
    - Middle ground? Cache.
    - Closer to the CPU
    - Usually arranged in a level hierarchy
    - Cache Miss means you're trying to access memory that is not ye tin the cache.
    - Cache Hit means the memory you want is in the cache already. 

Numbers and Values:
Values exist regardless of how we write them down.
    - There are 12 apples:
        - 12 apples(decimal)
        - 1100 apples(binary)
        - C apples(hexadecimal)
(The number of apples is the same-- we're just writing it in different bases. Like different languages!)

Number Bases:
The number base refers to how many individual digits that number system has.
    - Decimal has 10 digits(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) so it is base 10.
    - Binary has 2 digits (0, 1) so it is base 2. Abinary digit is called a bit for short.
    - Hexadecimal has 16 digits(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F) so it is base 16.
    (Hexadecimal is often called "hex" for short.)
    - Octal has 8 digits(0, 1, 2, 3, 4, 5, 6, 7) so it is base 8. (Not frequently used.)

Terminology:
    - Byte: 8 bits. Max value: 255 decimal, FF hex. Min value 0.
    - Nibble: 4 bits. Max value: 15 decimal, F hex. Min value 0.
    - Octet: synonym for byte.
    - Decimal: A base-10 numbering system, the one you already know.
    - Hexadecimal or hex: A base-16 numbering system.
    - Binary: A base-2 numbering system.
    - Octal: A rarely-used base-8 numbering stysem.

The Octal Trap: 
Even though octal (base 8) is rarely used, you can specify octal numbers in many languages with a leading zero:
    int x = 12; // Decimal
    int y = 012; // Octal, decimal value 10!
Don't pad decimal numbers with leading zeros!

Bitwise Operations:
    - A bitwise operation operates on one or more bit patterns or binary numerals at the level of their individual bits. 
    - It is a fast and simple action, directly supported by the processor, and is used to manipulate values for comparisons and calculations.
    - Bitwise operations are contrasted by byte-level operations which characterize the bitwise operators' logical counterparts, the AND, OR and NOT operators. Instead of performing on individual bits, byte-level operators perform on strings of eight bits (known as bytes) at a time.

    Right Shift:
    - The symbol of right shift operator is >>. For its operation, it requires two operands. It shifts each bit in its left operand to the right. The number following the operator decides the number of places the bits are shifted (i.e. the right operand). Thus by doing ch >> 3 all the bits will be shifted to the right by three places and so on.

    Example:

    If the variable ch contains the bit pattern 11100101, then ch >> 1 will produce the result 01110010, and ch >> 2 will produce 00111001.
    Here blank spaces are generated simultaneously on the left when the bits are shifted to the right. When performed on an unsigned type, the operation performed is a logical shift, causing the blanks to be filled by 0s (zeros). When performed on a signed type, the result is technically undefined and compiler dependent,[5] however most compilers will perform an arithmetic shift, causing the blank to be filled with the sign bit of the left operand.

    Left Shift:
    - The symbol of left shift operator is <<. It shifts each bit in its left-hand operand to the left by the number of positions indicated by the right-hand operand. It works opposite to that of right shift operator. Thus by doing ch << 1 in the above example we have 11001010. Blank spaces generated are filled up by zeroes as above.

    Left shift can be used to multiply an integer by powers of 2 as in

    int i = 4; /* bit pattern equivalent is binary 100 */
    int j = i << 2; /* makes it binary 10000, which multiplies the original number by 4 i.e. 16 */

What is the stack?
    - Just liek the stack data structure you already know.
    - PUSH and POP are standard operations.
    - Stack data is stored in RAM.
    - The stack pointer keeps track of the address of the top of the stack.
    - Typically the stack grows down from the higher memory addresses.

A Minimal Stack:
    - A stack needs somewhere to store data: RAM in this case.
    - A stack needs to keep track of where the top of the stack is: stack pointer.
    - A stack needs functionality to push and pop: the PUSH and POP instructions.
    - That's it!

How is it used?
    - Temporary storage variables.
    - Return address from the subroutine.
    - Storage of registers and CPU state while handling an interrupt.
    - Allocation of local variables for a subroutine. 

Interrupts:
    - Interrupts are commonly generated by peripherals who need to alert the CPU that some work needs to be done, e.g. a key has been pressed and needs to be handled.
    - When an interrupt occurs, the current state of the processor is saved on the stack, and execution continues at the address of the interrupt handler.
    - After the handler completes the processor state is popped off the stack and execution resumes like nothing ever happened.

Interrupt Vactor Table:
    - Most CPUs have a lookup table: Interrupt Vector Table.
    - When, say, Interrupt #2 occurs, the address of the handler is looked up in the Interrupt Vector Table.
    - It's an array of pointer to handlers, one per interrupt.
    - Different CPUs keep the table in different parts of RAM.

What are Subroutines?
    - Think of them as functions, the concept you already know from higher-level languages.
    - In assembly, we CALL a subroutine at a particular address.
    - Then we RET (return) from that subroutine to pick up where we left off, just like a funciton does in a high-level language. 

Linimations:
    - CPUs are pretty simple machines.
    - No arguments.
    - No return values.
    - These can be implemented in a variety of ways, however. (Clearly it's possible--other languages do it!)

Use of the Stack:
    - When we CALL a subroutine, we need to store the return address somewhere so we know wehre to go when we hit the RET instructions.
    - CPUs tend to use the stack for this.
    - CALL will push the address of the instruction after it on the stack, then move the PC to the subroutine address.
    - RET will pop the return address off the stack, and store it in the PC.
    - Use anyplace you'd use funcitons in a higher-level language.
        - Dry principle.
    - High-level languages eventually use CALL and RET deep down the implement functions.