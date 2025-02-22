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

int64_t internetAtkin(int64_t** buf, int64_t max) {
	char* array = malloc(sizeof(char) * max);
	for (int64_t i = 0; i < max; ++i) {
		// Bitwise arithmetic that returns 0 for even and 1 for odd
		array[i] = (char) 0;
	}
	// Find prime
	int sequence[] = { 2, 4 };
	int index = 0;
	int k1 = 0, k = 0;

	// Condition 1
	double xUpper = sqrt(max / 4) + 1;
	int x = 1;
	int y = 0;

	while (x < xUpper) {
		index = 0;
		k1 = 4 * x * x;
		y = 1;
		if (x % 3 == 0) {
			while (true) {
				k = k1 + y * y;
				if (k >= max) {
					break;
				}
				array[k] = !array[k];
				y += sequence[(++index & 1)];
			}
		} else {
			while (true) {
				k = k1 + y * y;
				if (k >= max) {
					break;
				}
				array[k] = !array[k];
				y += 2;
			}
		}
		x++;
	}

	// Condition 2
	xUpper = sqrt(max / 3) + 1;
	x = 1;
	y = 0;

	while (x < xUpper) {
		index = 1;
		k1 = 3 * x * x;
		y = 2;
		while (true) {
			k = k1 + y * y;
			if (k >= max) {
				break;
			}
			array[k] = !array[k];
			y += sequence[(++index & 1)];
		}
		x += 2;
	}

	// Condition 3
	xUpper = (int) sqrt(max);
	x = 1;
	y = 0;

	while (x < xUpper) {
		k1 = 3 * x * x;
		if ((x & 1) == 0) {
			y = 1;
			index = 0;
		} else {
			y = 2;
			index = 1;
		}
		while (y < x) {
			k = k1 - y * y;
			if (k < max) {
				array[k] = !array[k];
			}
			y += sequence[(++index & 1)];
		}
		x++;
	}

	array[2] = true;
	array[3] = true;
	for (int n = 5; n <= (int) sqrt(max); n++) {
		if (array[n]) {
			int n2 = n * n;
			for (k = n2; k < max; k += n2) {
				array[k] = false;
			}
		}
	}

	// Display prime
	int64_t primeCount = 3;
	for (int64_t i = 7; i < max; i+=2) {		
		if (array[i]) {
			++primeCount;
		}
	}
	// Scan for primes in isPrime
	int64_t* primes = malloc(sizeof(int64_t) * primeCount);
	primes[0] = 2;
	for (int64_t i = 3, j = 1; i < max; i+=2) {
		if (array[i]) {
			primes[j] = i;
			++j;
		}
	}
	free(array);
	*buf = primes;
	return primeCount;
}

int64_t sieveOfAtkin(int64_t** buf, int64_t max) {
	
	char* isPrime = malloc(sizeof(char) * max);
	
	for (int64_t i = 0; i < max; ++i) {
		// Bitwise arithmetic that returns 0 for even and 1 for odd
		isPrime[i] = (char) 0;
	}

	clock_t begin = clock(); 
	// Condition 1
	int64_t sequence[] = {2,4};
	int64_t xUpper = (int64_t) ceil(sqrt(max / 4)) + 1;
	
	for (int64_t x = 1; x < xUpper; x++) {
		int64_t xres = 4 * x * x;
		int64_t yUpper = sqrt(max - xres) + 1;
		int64_t index = 0;
		if (x % 3 == 0) {
			for (int64_t y = 1; y < yUpper; y+=sequence[(++index & 1)]) {
				
				int64_t n = xres + (y * y);
				int64_t r = n % 60;
				// 1, 13, 17, 29, 37, 41, 49, or 53
				// r == 1 || r == 13 || r == 37 || r == 49 ||  r == 17 || r == 29 || r == 41 || r == 53
				if (n < max) {
					isPrime[n] = !isPrime[n];
				}
			}
		} else {
			for (int64_t y = 1; y < yUpper; y+=2) {
				
				int64_t n = xres + (y * y);
				int64_t r = n % 60;
				if (n < max) {
					isPrime[n] = !isPrime[n];
				}
			}
		}

	}
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	// Condition 2
	begin = clock();
	xUpper = (int64_t) ceil(sqrt(max / 3)) + 1;
	for (int64_t x = 1; x < xUpper; x+=2) {
		int64_t index = 1;
		int64_t xres = 3 * x * x;
		int64_t yUpper = (int64_t) sqrt(max - xres) + 1;
		for (int64_t y = 2; y < yUpper; y+=sequence[++index & 1]) {
			int64_t n = xres + (y * y);
			if (n < max) {
				isPrime[n] = !isPrime[n];
			}
		}
	}
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	// Condition 3
	begin = clock();
	xUpper = (int64_t) sqrt(max) + 1;
	for (int64_t x = 1; x < xUpper; x++) {
		int64_t index = (x & 1);
		int64_t xres = 3 * x * x;
		// int64_t yUpper = (int64_t) sqrt(max) + 1;
		for (int64_t y = 1 + (x & 1); y < x; y += sequence[++index & 1]) {
			int64_t n = xres - (y * y);
			if (n < max) {
				isPrime[n] = !isPrime[n];
			}
		}
	}
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition: %d sec %d ms\n", ms / 1000, ms % 1000);
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
	printf("Time for condition: %d sec %d ms\n", ms / 1000, ms % 1000);	
	
	
	// Process sieve
	begin = clock();
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
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for condition: %d sec %d ms\n", ms / 1000, ms % 1000);
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
	
	clock_t begin = clock();
	int index = 100000000;
	
	int64_t prime = nthPrimeAtkin(index);
	
	printf("Prime #%I64d is %I64d\n", index, prime);
	int ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Time for Atkin: %d sec %d ms\n", ms / 1000, ms % 1000);
	
	begin = clock();
	
	prime = nthPrimeEratosthenes(index);
	
	ms = ((clock() - begin) * 1000 / CLOCKS_PER_SEC);
	printf("Prime #%I64d is %I64d\n", index, prime);
	printf("Time for Eratosthenes: %d sec %d ms\n", ms / 1000, ms % 1000);

	return 0;
}