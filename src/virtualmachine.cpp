#include "../include/virtualmachine.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

vm::vm(FILE *inputfile, FILE * input, FILE* output) {
    this->memsize = INIT_SIZE;
    this->memory = new char[INIT_SIZE];
    this->current = this->memory;
    memset(this->memory, 0, sizeof(char) * INIT_SIZE);
    if (input == nullptr) {
        this->input = stdin;
    }
    if (output == nullptr) {
        this->outputFile = stderr;
    }
    this->inputFile = inputfile;
    this->pc = 0;
}

vm::~vm() {
    if (this->memory) {
        delete[] this->memory;
    }
    this->memory = nullptr;
    this->current = nullptr;
    this->memsize = 0;
    if (this->inputFile != stdin) {
        fclose(this->inputFile);
    }
    this->inputFile = nullptr;
    if (this->outputFile != stderr) {
        fclose(this->outputFile);
    }
    this->outputFile = nullptr;
    if (this->input != stdin) {
        fclose(this->input);
    }
    this->input = nullptr;
}

void vm::shiftright() {
    // first check if memory allow
    if (this->current == this->memory + this->memsize - 1) {
        size_t offset = this->current - this->memory;
        // if not, double the size of memory
        size_t newsize = this->memsize * 2;
        char *newmemory = new char[newsize];
        memset(newmemory, 0, sizeof(char) * newsize);
        // copy the old memory to new memory
        memcpy(newmemory, this->memory, this->memsize);
        // delete the old memory
        delete[] this->memory;
        // assign the new memory to old memory
        this->memory = newmemory;
        // update the size of memory
        this->memsize = newsize;
        this->current = this->memory + offset;
    }
    // move the pointer to right
    this->current++;
}

void vm::shiftleft() {
    // first check if memory allow
    if (this->current == this->memory) {
        fprintf(stderr, "Error: pointer out of range at %ld\n", ftell(this->inputFile));
        exit(1);
    }
    // move the pointer to left
    this->current--;
}

void vm::add() {
    // add 1 to the current pointer
    (*this->current)++;
}

void vm::minus() {
    // minus 1 to the current pointer
    (*this->current)--;
}

void vm::output() {
    // output the current pointer
    fputc(*this->current, this->outputFile);
}

void vm::getinput() {
    // input to the current pointer
    *this->current = fgetc(this->input);
}

void vm::jumpZ() {
    // if the current pointer is 0, jump to the corresponding ']'
    // so this scope would be skipped
    if (*(this->current) == 0) {
        while(fetch() && ((char) this->pc) != ']');
    }
    else {
        // push the current position to stack
        this->loopStack.push(ftell(this->inputFile));
    }
}

void vm::jumpNZ() {
    // if the current pointer is not 0, jump to the corresponding '['
    if (*this->current != 0) {
        if (this->loopStack.empty()) {
            fprintf(stderr, "Error: no corresponding '['\n");
            exit(1);
        }
        // jump to the corresponding '['
        fseek(this->inputFile, this->loopStack.top(), SEEK_SET);
   }
    else {
         // pop the stack
         this->loopStack.pop();
    }
}

bool vm::fetch() {
    pc = fgetc(this->inputFile);
    if (pc == EOF) {
        pc = 0;
        return false;
    }
    return true;
}

int vm::run() {
    while(fetch()) {
        // fprintf(stderr, "We get %c\n", (char) pc);
        switch((char) pc) {
            case '>':
                shiftright();
                break;
            case '<':
                shiftleft();
                break;
            case '+':
                add();
                break;
            case '-':
                minus();
                break;
            case '.':
                output();
                break;
            case ',':
                getinput();
                break;
            case '[':
                jumpZ();
                break;
            case ']':
                jumpNZ();
                break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                break;
            default:
                fprintf(stderr, "Error: invalid character %c\n", (char) pc);
                break;
        }
    }
    return 0;
}