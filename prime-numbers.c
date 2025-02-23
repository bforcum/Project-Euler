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
	
	clock_t begin = clock();

	int64_t primeCount = 1;
	int64_t maxPrimeCount = 1 + (int64_t) (1.25 * max / log(max));
	int64_t* primes = malloc(sizeof(int64_t) * maxPrimeCount);
	primes[0] = 2;
	
	for (int64_t i = 3; i < max; i+=2) {		
		if (isPrime[i]) {
			primes[primeCount] = i;
			++primeCount;
		}
	}
	// Scan for primes in isPrime
	primes = (int64_t *) realloc(primes, sizeof(int64_t) * maxPrimeCount);

	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time of processing 5: %d sec %d ms\n", ms / 1000, ms % 1000);

	free(isPrime);

	*buf = primes;
	return primeCount;

}

int64_t sieveOfAtkin(int64_t** buf, int64_t max) {
	
	// Initialize array filled with 0
	char* isPrime = calloc(max, sizeof(char));

	clock_t begin = clock(); 
	// Condition 1
	int64_t sequence[] = {2,4};
	int64_t xUpper = (int64_t) ceil(sqrt(max / 4)) + 1;
	
	for (int64_t x = 1; x < xUpper; x++) {
		int64_t xres = 4 * x * x;
		int64_t yUpper = sqrt(max - xres) + 1;
		int64_t index = 0;
		int64_t y = 1;

		if (x % 3 == 0) {
			while (true) {
				int64_t n = xres + (y * y);
				if (n >= max) {
					break;
				}
				isPrime[n] = !isPrime[n];

				y += sequence[(++index & 1)];
			}
		} else {
			while (true) {
				
				int64_t n = xres + (y * y);
				if (n >= max) {
					break;
				}
				isPrime[n] = !isPrime[n];
				y += 2;
			}
		}
	}
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition 1: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	// Condition 2
	begin = clock();
	xUpper = (int64_t) ceil(sqrt(max / 3)) + 1;
	for (int64_t x = 1; x < xUpper; x+=2) {
		int64_t index = 1;
		int64_t xres = 3 * x * x;
		int64_t y = 2;
		
		while (true) {
			int64_t n = xres + (y * y);
			if (n >= max) {
				break;
			}
			isPrime[n] = !isPrime[n];

			y+=sequence[++index & 1];
		}
	}
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition 2: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	// Condition 3
	begin = clock();
	xUpper = (int64_t) sqrt(max) + 1;
	for (int64_t x = 1; x < xUpper; x++) {
		int64_t xres = 3 * x * x;
		
		// If x is odd, index and y are 2 (after index is incremented)
		// If x is even, index and y is 1 (after index is incremented)
		int64_t index = (x & 1);

		for (int64_t y = 1 + (x & 1); y < x; y += sequence[++index & 1]) {
			int64_t n = xres - (y * y);
			if (n < max) {
				isPrime[n] = !isPrime[n];
			}
		}
	}
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition 3: %d sec %d ms\n", ms / 1000, ms % 1000);
	begin = clock();

	if (max > 2) {
		isPrime[2] = (char) 1;
	}
	if (max > 3) {
		isPrime[3] = (char) 1;
	}

	for (int64_t r = 5; r < (int64_t) sqrt(max) + 1; r++) {
		if (isPrime[r]) {
			for (int64_t i = r * r; i <= max; i += r * r)
				isPrime[i] = (char) 0;
		}
	}
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for filtering 4: %d sec %d ms\n", ms / 1000, ms % 1000);	
	
	
	// Process sieve
	begin = clock();
	
	int64_t primeCount = 1;
	int64_t maxPrimeCount = 1 + (int64_t) (1.25 * max / log(max));
	int64_t* primes = malloc(sizeof(int64_t) * maxPrimeCount);
	primes[0] = 2;
	
	for (int64_t i = 3; i < max; i+=2) {		
		if (isPrime[i]) {
			primes[primeCount] = i;
			++primeCount;
		}
	}
	// Scan for primes in isPrime
	primes = (int64_t *) realloc(primes, sizeof(int64_t) * maxPrimeCount);

	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time of processing 5: %d sec %d ms\n", ms / 1000, ms % 1000);
	begin = clock();
	
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
	
	int index = 10000000;
	
	clock_t begin = clock();
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