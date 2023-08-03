#ifndef __VRITUALMACHINE__
#define __VRITUALMACHINE__

#include <ctype.h>
#include <cstdio>
#include <stack>
#include <vector>

#define INIT_SIZE 8

class vm {
    private:
        // Memory pool used by the vm
        char *memory;
        // current pointer
        char *current;
        // the size of memory pool
        std::size_t memsize;
        // output IO PORT, default stderr
        FILE *outputFile;
        // input File, where the commands come from, must be set by user
        FILE *inputFile;
        // INPUT IO PORT, default stdin
        FILE *input;
        // used to track '[]' correspondance
        std::stack<std::size_t> loopStack;
        // current command
        int pc;
    protected:
        bool fetch();
        // for operator >
        void shiftright();
        // for operator < 
        void shiftleft();
        // for operator +
        void add();
        // for operator -
        void minus();
        // for operator .
        void output();
        // for operator ,
        void getinput();
        // for operator [
        void jumpZ();
        // for operator ]
        void jumpNZ();
    public:
        vm(FILE * inputfile, FILE* input = nullptr, FILE* output = nullptr);
        ~vm();
        int run();
};

#endif