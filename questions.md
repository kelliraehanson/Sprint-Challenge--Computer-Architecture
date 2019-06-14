What are some examples of instructions handled by the CPU (as opposed to the ALU)?

Answer: The the alu does all the math operations and comparations.
cpu does the rest: call, print, reading, and writing from ram.

Convert the 8-bit hex number 0xB7 to binary.

Answer: 1011011

Convert the 8-bit binary number 0b10101011 to hex.

Answer: xAB
1010 =  A
1011 = B

Describe the bitwise operations needed to turn off the 5th bit from the right of 0b01111100.

Answer: 
1111100
&1101111
1101100

Why do people tend to gravitate towards base-10 number systems while computers do better with base-2?

Answer: The reason computers use the base-2 system is because it makes it a lot easier to implements them with current technology. We originally had a base-10 number system because humans have 10 fingers to count on so it is based on 10. If we had only 8 fingers it would probably be a base-8 based number system. 

Create an AND mask to preserve the last 3 right-hand bits of any 8-bit number.

Answer: 
01111110
&0000111
00000110

Describe the relative strengths and weaknesses RAM versus registers.

Answer: 

Ram: there is a lot more of it and you can add more if you want to, but it is not as fast.

Register is really fast and is more expensive and you can not change it later. The storage complicity is small and it is in the chip.

Describe the difference in what happens when a JUMP command is executed versus a CALL command.

Answer:

Jump: you go from once pointer counter to another.
Call: you store a return in the stack of the pointer you want to go back to. 
both you are put in a subroutine. 

In js example of jump: The end of a for loop.
In js example of call: Call would be a function and then your return to next line in code.

Why is a CPU stack useful in assembly language?

Answer: Storing temporary variables, return addresses, temporary values, and passing arguments to subroutines.

Bonus:

Why does the stack grow downwards?

Answer: Because programs can vary in length and you don't know where the program will end and stack will start.


