#include "../include/transformer.h"
#include <stdio.h>
#include "../include/virtualmachine.h"
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

transform::transform(FILE* input, FILE* output) {
    this->input = input;
    this->output = output;
    this->memory = new char[INIT_SIZE];
    this->memsize = INIT_SIZE;
    this->current = this->memory;
    this->pc = 0;
    this->current_dep = 0;
    memset(this->memory, 0, sizeof(char) * this->memsize);
}

transform::~transform() {
    if (this->input != nullptr) {
        fclose(this->input);
    }
    if (this->output != nullptr) {
        fclose(this->output);
    }
    this->input = nullptr;
    this->output = nullptr;
    if (this->memory) {
        delete[] this->memory;
    }
    this->memory = nullptr;
    this->current = nullptr;
    this->memsize = 0;
    this->pc = 0;
    this->current_dep = 0;
}

string transform::getName(size_t offset) {
    if (offset > this->memsize) {
        fprintf(stderr, "Error: %ld is out of range\n", offset);
        return "";
    }
    return "memory[" + to_string(offset) + "]";
}

bool transform::fetch() {
    pc = fgetc(input);
    if (pc == EOF) {
        return false;
    }
    return true;
}

void transform::dump(const std::string& instr) {
    for (int i = 0; i < this->current_dep; ++i) {
        fprintf(output, "\t");
    }
    fprintf(output, "%s\n", instr.c_str());
}

int transform::start() {
    dump("#include <stdio.h>\n");
    dump("char* initmemory();");
    dump("char* memory = NULL;\n");
    dump("int main() {");
    this->current_dep++;
    dump("memory = initmemory();");
    do {
        switch (pc) {
            case '<':
                shiftleft();
                break;
            case '>':
                shiftright();
                break;
            case '.':
                getoutput();
                break;
            case ',':
                getinput();
                break;
            case '+':
                add();
                break;
            case '-':
                minus();
                break;
            case '[':
                jumpZ();
                break;
            case ']':
                jumpNZ();
                break;
            default:
                break;
        }
    } while(fetch());
    this->current_dep--;
    dump("}\n");
    dump_memory();
    return 0;
}

void transform::shiftleft() {
    if (this->current == this->memory) {
        fprintf(stderr, "Error: pointer out of range at %ld\n", ftell(this->input));
        exit(1);
    }
    this->current--;
}

void transform::shiftright() {
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

void transform::add() {
    dump(getName(this->current - this->memory) + "++;");
}

void transform::minus() {
    dump(getName(this->current - this->memory) + "--;");
}

void transform::getoutput() {
    dump("putchar(" + getName(this->current - this->memory) + ");");
}

void transform::getinput() {
    dump(getName(this->current - this->memory) + " = getchar();");
}

void transform::jumpZ() {
    dump("while(" + getName(this->current - this->memory) + " != 0) {");
    this->current_dep++;
}

void transform::jumpNZ() {
    dump("}");
    this->current_dep--;
}

void transform::dump_memory() {
    dump("char *initmemory() {");
    this->current_dep++;
    dump("static char mem[" + to_string(this->memsize) + "] = {0};");
    dump("return mem;");
    this->current_dep--;
    dump("}");
}