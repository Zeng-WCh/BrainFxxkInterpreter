#include <stdio.h>

char* initmemory();
char* memory = NULL;

int main() {
	memory = initmemory();
	memory[0] = getchar();
	putchar(memory[0]);
}

char *initmemory() {
	static char mem[8] = {0};
	return mem;
}
