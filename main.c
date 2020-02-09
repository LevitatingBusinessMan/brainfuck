#include <stdio.h>
#include <stdlib.h>

#define INST_STACK_LENGTH 512
#define STACK_SIZE 30000

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
		perror("Unable to open file");
		return EXIT_FAILURE;
	}

	//Instruction stack is 512 bytes
	char inst[INST_STACK_LENGTH] = {0};

	//There are 8 instructions supported
	char *av_insts[8] = {">", "<", "+", "-", ".", ",", "[", "]"};

	//Write the stack
	char c;
	int i = 0, j;
	while ((c = fgetc(fs))  != EOF ) {

		//printf(&c);

		if (i > INST_STACK_LENGTH -1) {
			perror("Maximum instruction stack reached.");
			return EXIT_FAILURE;
		} 

		//Add to instructions if valid inst
		for (j=0; j < 8; j++) {
			if (*av_insts[j] == c) {
				//printf("%c %d\n", c, i);
				inst[i] = c;
				i++;
			}
		}
		
	}

	puts("Instruction stack:");
	printf(inst);



	//Setup WM
	char stack[STACK_SIZE] = {0}; //Initilize stack
	char *sp = stack; //Point sp to stack

	//Run program
	for (i = 0, i == NULL, i++) {

	}

	fclose(fs);



}
