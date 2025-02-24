#include "config.h"

#include "sieve-atkin.h"
#include "sieve-eratosthenes.h"

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
	
	int64_t index = 100000000;
	
	// clock_t begin = clock();
	// int64_t prime = nthPrimeEratosthenes(index);
	// int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	
	// printf("Prime #%I64d is %I64d\n", index, prime);
	// printf("Time for Eratosthenes: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	clock_t begin = clock();
	int64_t prime = nthPrimeAtkin(index);
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	
	printf("Prime #%I64d is %I64d\n", index, prime);
	printf("Time for Atkin: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	

	return 0;
}