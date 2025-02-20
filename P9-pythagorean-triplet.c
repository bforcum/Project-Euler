#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


int main (int argc, char* argv[]) {
	for (int a = 0; a < 500; a++) {
		for (int b = 0; b < 500; b++) {
			double c = sqrt(a * a + b * b);
			if (c - floor(c) == 0) {
				if (a + b + c == 1000) {
					printf("Triple is %d, %d, %d\n", a, b, (int) c);
				}
			}
		}
	}
}