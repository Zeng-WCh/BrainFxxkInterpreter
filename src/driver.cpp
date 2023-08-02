#include <iostream>
#include "../include/virtualmachine.h"

const char *msg = "Usage: %s <filename>\n";

int main(int argc, const char **argv){
    if (argc != 2) {
        fprintf(stderr, msg, argv[0]);
        exit(1);
    }
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        exit(1);
    }
    vm machine(input);
    return machine.run();
}