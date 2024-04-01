#include "../include/transformer.h"
#include "../include/virtualmachine.h"
#include <cstring>
#include <iostream>

const char *msg =
    "Usage: %s [--interprete|--transform|--LLVM] <filename> [-o <output>]\n";

int main(int argc, const char **argv) {
  if (argc < 2) {
    fprintf(stderr, msg, argv[0]);
    exit(1);
  }
  int mode = 0;
  FILE *input = nullptr;
  if (argv[1][0] == '-') {
    if (argc < 3) {
      fprintf(stderr, msg, argv[0]);
      exit(1);
    }
    if (strcmp(argv[1], "--interprete") == 0) {
      mode = 0;
    } else if (strcmp(argv[1], "--transform") == 0) {
      mode = 1;
    } else if (strcmp(argv[1], "--LLVM") == 0) {
      mode = 2;
    } else {
      fprintf(stderr, msg, argv[0]);
      exit(1);
    }
    input = fopen(argv[2], "r");
  }

  if (input == nullptr)
    input = fopen(argv[1], "r");
  if (input == nullptr) {
    fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
    exit(1);
  }

  if (mode == 0) {
    // interprete
    vm machine(input);
    int status = machine.run();
    return status;
  } else {
    // trans to C code
    if (argc < 5) {
      fprintf(stderr, msg, argv[0]);
      exit(1);
    }
    FILE *output = fopen(argv[4], "w");
    if (output == nullptr) {
      fprintf(stderr, "%s can not be opened\n", argv[4]);
      exit(1);
    }
    fclose(output);
    output = fopen(argv[4], "a");
    transform tm(input, output);
    int status = tm.start();
    return status;
  }
}