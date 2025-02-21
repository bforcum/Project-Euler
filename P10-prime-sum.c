#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

/**
 * Incorrect answers:
 * 1179908154
 * 
 */

int64_t sieveOfEratosthenes(int64_t **buf, int64_t max) {
	
	// sqrt(max) is the maximum factor that could prove numbers in range composite
	int64_t maxFactor = (int64_t) sqrt(max);
	char* isPrime = malloc(sizeof(char) * max);
	
	// Initialize 2 and all odd numbers as primes
	isPrime[2] = (char) 1;
	for (int64_t i = 3; i < max; ++i) {
		// Bitwise arithmetic that returns 0 for even and 1 for odd
		isPrime[i] = (char) (i & 1);
	}
	
	// For each prime, set isPrime for all of its factors to 0
	for (int64_t i = 3; i <= maxFactor; i+=2) {
		if (0 == isPrime[i]) {
			continue;
		}
		// Start at i*i because all lesser factors will already be marked.
		for (int64_t j = i * i; j < max; j += i * 2) {
			isPrime[j] = (char) 0;
		}
	}
	
	int64_t primeCount = 1;
	for (int64_t i = 3; i < max; i+=2) {		
		if (isPrime[i]) {
			++primeCount;
		}
	}
	// Scan for primes in isPrime
	int64_t* primes = malloc(sizeof(int64_t) * primeCount);
	primes[0] = 2;
	for (int64_t i = 3, j = 1; i < max; i+=2) {
		if (isPrime[i]) {
			primes[j] = i;
			++j;
		}
	}
	free(isPrime);

	*buf = primes;
	return primeCount;

}

// Get the nth prime from a sieve algorithm
int64_t nthPrime(int64_t n) {
	int64_t upperBound = (int64_t) (3 + (n - 1) * (log(n) + log(1 + log(n))));
	int64_t* primes = malloc(1);
	int64_t count = sieveOfEratosthenes(&primes, upperBound);
	if (count < n) {
		printf("Error - not enough primes found");
	}
	int64_t result = primes[n-1];
	free(primes);
	return result;
}

int64_t primeSum(int64_t upperBound) {
	int64_t* primes;
	int64_t count = sieveOfEratosthenes(&primes, upperBound);
	int64_t sum = 0;
	for (int64_t i = 0; i < count; i++) {
		if (i >= 99 && i < 119) {
			printf("Prime #%d is %d\n", i + 1, primes[i]);
		}
		sum = ((int64_t)sum) + primes[i];
	}
	free(primes);
	return sum;
}

int main(int argc, int* argv[]) {
	
	clock_t begin = clock();
	int max = 2000000;
	
	int64_t sum = primeSum(max);
	
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Sum of all primes under %I64d is %I64d\n", max, sum);
	printf("Time: %d sec %d ms\n", ms / 1000, ms % 1000);

	return 0;
}