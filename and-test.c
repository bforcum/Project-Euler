#include <stdio.h>

int main(int arc, char* argv[]) {
	int val1 = 1 && 10;
	int val2 = 0 && 1;
	printf("%d, %d", val1, val2);
}