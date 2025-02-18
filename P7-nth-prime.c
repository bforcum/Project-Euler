#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

void sieveOfEratosthenes(int64_t* buf, int64_t n) {
	// Set an upper bound for the range of the nth prime
	int64_t upperBound = (int64_t) (3 + (n - 1) * (log(n) + log(1 + log(n))));
	// sqrt(upperBound) is the maximum factor that could prove numbers in range composite
	int64_t maxFactor = (int64_t) sqrt(upperBound);
	char* isPrime = malloc(sizeof(char) * upperBound);
	
	// Initialize 2 and all odd numbers as primes
	isPrime[2] = (char) 1;
	for (int64_t i = 3; i < upperBound; ++i) {
		// Bitwise arithmetic that returns 0 for even and 1 for odd
		isPrime[i] = (char) (i & 1);
	}
	
	// For each prime, set isPrime for all of its factors to 0
	for (int64_t i = 3; i <= maxFactor; i+=2) {
		if (0 == isPrime[i]) {
			continue;
		}
		// Start at i*i because all lesser factors will already be marked.
		for (int64_t j = i*i; j < upperBound; j += i * 2) {
			isPrime[j] = (char) 0;
		}
	}
	
	// Scan for primes in isPrime
	buf[0] = 2;
	for (int64_t i = 3, j = 1; i < upperBound && j < n; i+=2) {		
		if (isPrime[i]) {
			buf[j] = i;
			++j;
		}
	}
	free(isPrime);
	return;

}

// Get the nth prime from a sieve algorithm
int64_t nthPrimeSieve(int64_t n) {
	int64_t* primes = malloc(sizeof(int64_t) * n);
	sieveOfEratosthenes(primes, n);
	int64_t prime = primes[n-1];
	free(primes);
	return prime;
}

bool isPrime(int64_t num, int primeCount, int64_t primes[]) {
	bool isPrime = true;
	for (int k = 0; k < primeCount && isPrime; k++) {
		isPrime = 0 < num % primes[k];
	}
	return isPrime;
}
int64_t worseNthPrime(int n) {
	int64_t* primes = malloc(sizeof(int64_t) * n);
	primes[0] = 2;
	for (int i = 1; i < n; i++) {
		int start = primes[i-1];
		for (int64_t j = start + 1; j < start * 2; j++) {
			if (isPrime(j, i, primes)) {
				primes[i] = j;
				break;
			}
		}
		if ((i + 1) % 5000 == 0) {
			printf("Prime #%d found: %d\n", i + 1, primes[i]);
		}
	}
	int64_t result = primes[n-1];
	free(primes);
	return result;
}
int64_t badNthPrime(int n) {
	int64_t* primes = malloc(sizeof(int64_t) * n);
	primes[0] = 2;
	int k = 1;
	for (int i = 3; k < n; i++) {
		if (isPrime(i, k, primes)) {
			primes[k] = i;
			// log every 5000th prime
			if ((k+1) % 5000 == 0) {
				printf("Prime #%d found: %d\n", k + 1, primes[k]);
			}
			k++;
		}
	}
	int64_t result = primes[n-1];
	free(primes);
	return result;
}

int main(int argc, int* argv[]) {
	clock_t begin = clock();
	int n = 10000000;
	int64_t prime = nthPrimeSieve(n);
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Prime #%d is: %d\n", n, prime);
	printf("Time: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	return 0;
}