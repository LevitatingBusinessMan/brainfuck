#include <stdio.h>
#include <stdlib.h>

#define INST_STACK_LENGTH 512
#define STACK_SIZE 30000

#define DEBUG 0
#define SHOW_INST_STACK 0

int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("Please specify a filename!");
		return 1;
	}

	//Pointer to filename
	char *filename = argv[1];

	//Open file for reading
	FILE *fs;

	if (!(fs = fopen(filename, "r"))) {
		perror("Error: ");
		return 1;
	}

	//Instruction stack is 512 bytes
	char inst[INST_STACK_LENGTH] = {0};

	//There are 8 instructions supported
	char *av_insts[8] = {">", "<", "+", "-", ".", ",", "[", "]"};

	//Write the stack
	char c;
	int i = 0, j;
	while ((c = getc(fs))  != EOF ) {

		if (i > INST_STACK_LENGTH -1) {
			fputs("Maximum instruction stack reached.", stderr);
			return 1;
		} 

		//Add to instructions if valid inst
		for (j=0; j < 8; j++) {
			if (*av_insts[j] == c) {
				inst[i] = c;
				i++;
			}
		}
		
	}

	//Close file
	fclose(fs);

	if (SHOW_INST_STACK) {
		puts("Instruction stack:");
		puts(inst);
	}

	//Setup WM
	char stack[STACK_SIZE] = {0}; //Initilize stack
	char *sp = stack; //Point sp to stack
	char *ip = inst; //Point ip to instruction stack

	//Run program
	while (*ip != 0) {
		switch (*ip) {

			//Next cell
			case '>':
				sp++;
				if (DEBUG)
					printf("nextcell (%d)\n", *sp);
				break;

			//Previous cell
			case '<':
				sp--;
				if (DEBUG)
					printf("prevcell (%d)\n", *sp);
				break;

			//Increment
			case '+':
				(*sp)++;
				if (DEBUG)
					printf("+ (%d)\n", *sp);
				break;
			
			//Decrement
			case '-':
				(*sp)--;
				if (DEBUG)
					printf("- (%d)\n", *sp);
				break;

			//Log
			case '.':
				if (DEBUG)
					printf("Logging (%d)\n", *sp);
				putchar(*sp);
				break;

			//Get
			case ',':
				if (DEBUG)
					puts("Getting");
				*sp = getchar();
				break;

			//Jump
			case '[':
 				if (*sp == 0) {
					if (DEBUG)
						puts("Skipping");
					int x = 0;
					while (1) {
						ip++;

						if (*ip == ']' && x == 0)
							break;

						//When finding another opening bracket,
						//ignore a closing bracket
						if (*ip == '[')
							x++;

						if (*ip == ']')
							x--;

						//No insts left
						if (*ip == 0) {
							fputs("Expected ']' before EOF", stderr);
							return 1;
						}
					}
				} else {
					if (DEBUG)
						printf("Not skipping (%d)\n", *sp);
				}
				break;

			//Jump back
			case ']':
 				if (*sp != 0) {
					if (DEBUG)
						puts("Reverting");
					int x = 0;
					while (1) {
						ip--;

						if (*ip == '[' && x == 0)
							break;

						//When finding another opening bracket,
						//ignore a closing bracket
						if (*ip == ']')
							x++;

						if (*ip == '[')
							x--;


						//No insts left
						if (ip == inst) {
							fputs("Expected '[' before ']'", stderr);
							return 1;
						}
					}
				} else {
					if (DEBUG)
						printf("Not reverting (%d)\n", *sp);
				}
				break;
		}
		ip++;
	}
}
