#ifndef __TRANSFORMER__
#define __TRANSFORMER__

#include <cstdio>
#include <ctype.h>
#include <string>

#include "virtualmachine.h"

class transform {
    private:
        FILE *input;
        FILE *output;
        char *memory;
        char *current;
        std::size_t memsize;
        int pc;
        int current_dep;
    protected:
        std::string getName(std::size_t pos);
        bool fetch();
        void shiftright();
        void shiftleft();
        void add();
        void minus();
        void getoutput();
        void getinput();
        void jumpZ();
        void jumpNZ();
        void dump(const std::string&);
        void dump_memory();
    public:
        transform(FILE *input, FILE *output);
        ~transform();
        int start();
};

#endif