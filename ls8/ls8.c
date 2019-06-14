#include <stdio.h>
#include "cpu.h"
#include <stdlib.h>

/**
 * Main
 */
int main(int argc, char *argv[])
{
  // printf("\n");
  // printf("** argc: %d **\n", argc);
  // for (int i = 0; i < argc; i++) {
  //   printf("%s\n", argv[i]);
  // }

  if (argc != 2) // Or < 2? This will check to make sure the user typed the correct things.
    {
        // If the user hasn't typed the correct things this tells them how to use it.
        fprintf(stderr, "** You must include the correct number of args! Please provide the name of the file you would like to run. **\n");
        fprintf(stderr, "** Example: ./ls8 examples/<filename>**\n");
        exit(1); // And then quit.
    }

  struct cpu cpu;

  cpu_init(&cpu);
  cpu_load(&cpu, argv);
  cpu_run(&cpu);

  return 0;
}
