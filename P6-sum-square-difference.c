#include <stdio.h>

int squareOfSum(int n) {
	int sum = n * (n + 1) / 2;
	return sum * sum;
}
int sumOfSquares(int n) {
	int sum = n * (n + 1) * (2 * n + 1) / 6;
	return sum;
}

int main(int argc, int* argv[]) {
	int answer = squareOfSum(100) - sumOfSquares(100);
	printf("%d", answer);
	return 0;
}