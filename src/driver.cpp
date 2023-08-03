#include <iostream>
#include <cstring>
#include "../include/virtualmachine.h"
#include "../include/transformer.h"

const char *msg = "Usage: %s [--interprete|--transform] <filename> [-o <output>]\n";

int main(int argc, const char **argv){
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
        mode = (strcmp(argv[1], "--interprete") == 0 ? 0 : 1);
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
    }
    else {
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