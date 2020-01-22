#include <stdio.h>
#include <stdlib.h>

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

	char inst[512];
	char *av_insts[8] = {">", "<", "+", "-", ".", ",", "[", "]"};

	//Write the stack
	int c, i, j;
	while ((c = fgetc(fs))/*  != EOF */) {

		if (c == -1) {
			printf("Last 6: %c%c%c%c%c%c\n", inst[i-6], inst[i-5], inst[i-4], inst[i-3], inst[i-2], inst[i-1]);
			break;
		}

/* 		if (c < 0) {
			break;
		} */

		if (i > 511) {
			perror("Maximum instruction stack reached.");
			return EXIT_FAILURE;
		} 

		//Add to instructions if valid inst
		for (j=0; j < 8; j++) {
			if (*av_insts[j] == c) {
				inst[i] = c;
				i++;
				break;
			}
		}
		
	}

	for (i=0; i < 512; i++)
		printf("%s", &inst[i]);

	fclose(fs);



}
