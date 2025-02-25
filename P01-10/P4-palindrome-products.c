#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool isPalindrome(int num) {
	int numDigits = ceil(log10(num + 1));
	char* digits = (char*) malloc(numDigits * sizeof(int));
	sprintf(digits, "%ld", num);
	bool isPalindrome = true;
	for (int i = 0; i < (numDigits + 1) / 2; i++) {
		if (digits[i] != digits[numDigits - i - 1]) {
			isPalindrome = false;
		}
	}
	free(digits);
	return isPalindrome;
}

int maxPalindrome() {
	int result = 0;
	for (int i = 999; i > 800; --i) {
		for (int j = 999; j > 800; --j) {
			if (isPalindrome(i*j)) {
				return i * j;
			}
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	printf("%d\n", maxPalindrome());
}