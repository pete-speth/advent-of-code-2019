#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads the next line from the stream 'file_p', and stores it in 'line'
char* readLine(FILE* file_p, int maxSize) {

	if(!file_p){
		perror("Invalid file pointer passed");
		return NULL;
	}

	int c = fgetc(file_p);
	if (c != EOF){
		char* line = malloc(sizeof(char[maxSize]));
		int charCount = 0;
		while(c != '\n'){
			line[charCount] = c;
			charCount++;
			c = fgetc(file_p);
		}

		return line;
	}

	return NULL;
}

void printIntArray(int* arr, int length) {
	for (int i=0; i<length; i++){
		printf("%d,",arr[i]);
	}
	printf("\n");
}
