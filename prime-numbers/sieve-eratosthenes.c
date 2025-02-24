#include "sieve-atkin.h"

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