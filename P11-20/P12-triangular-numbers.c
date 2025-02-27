#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "math.h"
#include "time.h"

int countFactors(int64_t num) {
	double maxFactorD = sqrt(num);
	int maxFactor = (int) maxFactorD;
	// If this number has a whole sqrt, then factors starts at 1. Otherwise, at 0
	int factors = maxFactorD == (double) maxFactor;

	for (int64_t i = 1; i < maxFactorD; i++) {
		factors += (num % i == 0) << 1;
	}
	return factors;
}
int64_t findTriangularNumWithFactors(int count) {
	int factors = 0;
	int64_t num = 0;
	for (int64_t i = 1; factors < count; i++) {
		num += i;
		factors = countFactors(num);
	}
	return num;
}


int main(int argc, int* argv) {
	clock_t begin = clock();
	
	int result = findTriangularNumWithFactors(500);
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	
	printf("%d is the first triangular number with 500 factors\n", result);
	printf("Time to find triangular number: %d sec %d ms\n", ms / 1000, ms % 1000);
}