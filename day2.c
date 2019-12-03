#include <stdio.h>
#include "aoc-utils.h"

int runProgram(int* program, int size);

int main(){
	FILE* file_p = fopen("input/day2.txt","r");

	char* input;
	input = readLine(file_p,500);

	// read the inputs into an array
	int program[500];
	char* token = strtok(input,",");
	int count = 0;
	while(token) {
		program[count] = atoi(token);
		token = strtok(NULL,",");
		count++;
	}

	// Need to make a copy, want to maintain the original program in memory for repeated runs
	int* programCp = malloc(count*sizeof(int));
	memcpy(programCp,program,count*sizeof(int));

	// run the original program given
	int output = runProgram(programCp, count);
	printf("Output for 1202 program is: %d\n",output);

	// run the program for all combinations of 1..99 in positions 1 & 2
	// trying to find the combination that gives the desired output
	for (int i=0; i<100; i++){
		for (int j=0; j<100; j++) {
			memcpy(programCp,program,count*sizeof(int));
			programCp[1] = i;
			programCp[2] = j;
			int output = runProgram(programCp, count);
			if (output == 19690720) {
				printf("%d input produces 19690720 as the output\n",i*100+j);
			}
		}
	}
}

int runProgram(int* program, int size) {
	for(int i=0; i < size;){
		if (program[i] == 99){
			break;
		} else if (program[i] != 1 && program[i] != 2) {
			printf("Invalid opcode at position %d\n",i);
			return 1;
		}

		int a = program[i+1];
		int b = program[i+2];
		int store = program[i+3];
		if (program[i] == 1) {
			program[store] = program[a]+program[b];
		} else if (program[i] == 2) {
			program[store] = program[a]*program[b];
		}
		i += 4;
	}

	return program[0];
}
