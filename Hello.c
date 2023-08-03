#include <stdio.h>

char* initmemory();
char* memory = NULL;

int main() {
	memory = initmemory();
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	memory[0]++;
	while(memory[0] != 0) {
		memory[1]++;
		memory[1]++;
		memory[1]++;
		memory[1]++;
		memory[1]++;
		memory[1]++;
		memory[1]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[2]++;
		memory[3]++;
		memory[3]++;
		memory[3]++;
		memory[4]++;
		memory[0]--;
		}
	memory[1]++;
	memory[1]++;
	putchar(memory[1]);
	memory[2]++;
	putchar(memory[2]);
	memory[2]++;
	memory[2]++;
	memory[2]++;
	memory[2]++;
	memory[2]++;
	memory[2]++;
	memory[2]++;
	putchar(memory[2]);
	putchar(memory[2]);
	memory[2]++;
	memory[2]++;
	memory[2]++;
	putchar(memory[2]);
	memory[3]++;
	memory[3]++;
	putchar(memory[3]);
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	memory[1]++;
	putchar(memory[1]);
	putchar(memory[2]);
	memory[2]++;
	memory[2]++;
	memory[2]++;
	putchar(memory[2]);
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	putchar(memory[2]);
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	memory[2]--;
	putchar(memory[2]);
	memory[3]++;
	putchar(memory[3]);
	putchar(memory[4]);
}

char *initmemory() {
	static char mem[8] = {0};
	return mem;
}
