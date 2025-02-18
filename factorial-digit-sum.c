#include <stdio.h>

int factorial(int num);

int sumDigits(int num);

int main() {
	for (int i = 0; i < 20; i++) {
		
		printf("Value: %d, Sneak: %d\n", sumDigits(factorial(i)), sumDigits(i * sumDigits(factorial(i-1))));
	}
}

int factorialDigitSum(int num) {
	
}

int factorial(int num) {
	if (num < 0) {
		return 0;
	}

	int result = 1;

	for (int i = 1; i <= num; i++) {
		result *= i;
	}
	
	return result;

	
}

int sumDigits(int num) {
	int total = 0;
	while (num > 0) {
		total += num % 10;
		num /= 10;
	}
	return total;
}