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

int64_t sieveOfAtkin(int64_t** buf, int64_t max) {
	
	char* isPrime = malloc(sizeof(char) * max);
	
	for (int64_t i = 0; i < max; ++i) {
		// Bitwise arithmetic that returns 0 for even and 1 for odd
		isPrime[i] = (char) 0;
	}
	
	if (max > 2) {
		isPrime[2] = (char) 1;
	}
	
	if (max > 3) {
		isPrime[3] = (char) 1;
	}
	if (max > 5) {
		isPrime[5] = (char) 1;
	}

	for (int64_t x = 1; 4 * x * x < max; x++) {
		int64_t xres = 4 * x * x;
		for (int64_t y = 1; y * y < max - xres; y++) {
			
			// Condition 1
			int64_t n = (4 * x * x) + (y * y);
			int64_t r = n % 60;
			if (n <= max) {
				// 1, 13, 17, 29, 37, 41, 49, or 53
				if (r == 1 || r == 13 || r == 17 || r == 29 || r == 37 || r == 41 || r == 49 || r == 53) {
					isPrime[n] = !isPrime[n];
				}
			}
		}
	}
	for (int64_t x = 1; 3 * x * x < max; x++) {
		int64_t xres = 3 * x * x;
		for (int64_t y = 1; y * y < max - xres; y++) {
			// Condition 2
			int n = (3 * x * x) + (y * y);
			int r = n % 60;
			if (n <= max) {
				// 7, 19, 31, or 43
				if (r == 7 || r == 19 || r == 31 || r == 43) {
					isPrime[n] = !isPrime[n];
				}
			}
		}
	}
	for (int64_t x = 1; x * x < max; x++) {
		for (int64_t y = 1; y * y < max && y < x; y++) {
			// Condition 3
			int n = (3 * x * x) - (y * y);
			int r = n % 60;
			if (n <= max) {
				// 11, 23, 47, or 59
				if (r == 11 || r == 23 || r == 47 || r == 59) {
					isPrime[n] = !isPrime[n];
				}
			}
		}
	}

	for (int64_t r = 5; r * r <= max; r++) {
		if (isPrime[r]) {
			for (int64_t i = r * r; i <= max; i += r * r)
				isPrime[i] = (char) 0;
		}
	}

	int64_t primeCount = 3;
	for (int64_t i = 7; i < max; i+=2) {		
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

// Get the nth prime from a prime-finding algorithm
int64_t nthPrimeEratosthenes(int64_t n) {
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
int64_t nthPrimeAtkin(int64_t n) {
	int64_t upperBound = (int64_t) (3 + (n - 1) * (log(n) + log(1 + log(n))));
	int64_t* primes = malloc(1);
	int64_t count = sieveOfAtkin(&primes, upperBound);
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
		sum = ((int64_t)sum) + primes[i];
	}
	free(primes);
	return sum;
}

int main(int argc, int* argv[]) {
	
	clock_t begin = clock();
	int index = 10000000;
	
	int64_t prime = nthPrimeEratosthenes(index);
	
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Prime #%I64d is %I64d\n", index, prime);
	printf("Time for Eratosthenes: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	begin = clock();
	
	prime = nthPrimeAtkin(index);
	
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Prime #%I64d is %I64d\n", index, prime);
	printf("Time for Atkin: %d sec %d ms\n", ms / 1000, ms % 1000);

	return 0;
}