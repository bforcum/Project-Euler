#include "sieve-eratosthenes.h"

int64_t sieveOfEratosthenes(int64_t **buf, int64_t max) {
	
	// sqrt(max) is the maximum factor that could prove numbers in range composite
	int64_t maxFactor = (int64_t) sqrt(max);

	int64_t array_size = (max + 31) / 32;
	int* isPrime = malloc(sizeof(int) * (max + 31) / 32);
	
	// Initialize prime numbers under 32
	isPrime[0] = 0b10100000100010100010100010101100;
	for (int64_t i = 1; i < (max + 31) / 32; ++i) {
		// even numbers start at 0 and odds at 1
		isPrime[i] = 0b10101010101010101010101010101010;
	}
	
	// For each prime, set isPrime for all of its factors to 0
	for (int64_t i = 3; i <= maxFactor; i+=2) {
		if (!getBit(isPrime, i)) {
			continue;
		}
		// Start at i*i because all lesser factors will already be marked.
		for (int64_t j = i * i; j < max; j += i * 2) {
			resetBit(isPrime, j);
		}
	}
	
	clock_t begin = clock();

	int64_t primeCount = 1;
	int64_t maxPrimeCount = 1 + (int64_t) (1.25 * max / log(max));
	int64_t* primes = malloc(sizeof(int64_t) * maxPrimeCount);
	primes[0] = 2;
	
	for (int64_t i = 3; i < max; i+=2) {		
		if (getBit(isPrime,i)) {
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
	int64_t* primes;
	int64_t count = sieveOfEratosthenes(&primes, upperBound);
	if (count < n) {
		printf("Error - not enough primes found\n");
	}
	int64_t result = primes[n-1];
	free(primes);
	return result;
}