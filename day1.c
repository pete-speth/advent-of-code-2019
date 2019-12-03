#include <stdio.h>
#include "aoc-utils.h"


int main() {
	FILE* file_p = fopen("input/day1.txt","r");
	if (!file_p) {
		perror("Could not open file");
		return EXIT_FAILURE;
	}

	char* line;
	int simpleSum = 0;	// the fuel for each module
	int sum = 0;	// includes the fuel required for the fuel for each module

	while((line = readLine(file_p,6)) != NULL){
		int n = atoi(line);
		int module = n/3-2;
		simpleSum += module;

		while(module > 0){
			sum += module;
			module = module/3-2;
		}
	}
	free(line);
	printf("The total fuel required for all modules is: %d\n",simpleSum);
	printf("Calculted fuel required for the fuel is: %d\n",sum);
}
