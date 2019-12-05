#include <stdio.h>
#include <stdlib.h>

int main(){
	int LOWER = 125730;
	int UPPER = 579831;

	// count all valid inputs between the given bounds
	int count = 0;
	for (int input = LOWER; input < UPPER; input++) {
		char str[6];
		sprintf(str,"%d",input);

		_Bool isValid = 0;
		for (int digit = 0; digit < 3; digit++){
			int a = str[digit] - '0';
			int b = str[digit+1] - '0';
			int c = str[digit+2] - '0';
			int d = str[digit+3] - '0';

			// input is not valid if digits are not increasing in size
			if (b < a || c < b || d < c) {
				isValid = 0;
				break;
			}

			// input must have exactly two consecutive same digits
			if (digit == 0 && a == b && a != c){
				isValid = 1;
			} else if (digit == 2 && c == d && b != c){
				isValid = 1;
			} else if (b == c && a != c && b != d){
				isValid = 1;
			}
		}

		if (isValid) {count++;}
	}

	printf("There are %d inputs which satisfy the conditions.\n", count);
}
