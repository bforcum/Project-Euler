#include <math.h>
#include <stdint.h>
#include <stdio.h>

int64_t largestPrimeFactor(int64_t num) {
	int64_t factor = 2;
	for (int64_t k = 2; k <= num;) {
		if (num % k == 0) {
			num = num / k;
			factor = k;
		} else {
			k++;
		}
	}
	return factor;
}

int main (int argc, char* argv[]) {
	int64_t input = 600851475143LL;
	int64_t result = largestPrimeFactor(input);
	printf("Largest prime factor of %I64d is: %d\n", input, result);
}



