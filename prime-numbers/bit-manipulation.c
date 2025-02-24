#include "bit-manipulation.h"


char getNthBit(char *buf, int64_t n) {
	// The byte that corresponds to n
	char byte = buf[n >> 3];
	// The bit of the byte that corresponds to n
	char mask = (1 << (n & 7));
	return (byte & (1 << (n & 7))) != 0;
}

void setNthBit(char *buf, int64_t n) {
	// Get the corresponding byte and bitwise-or it to set the correct bit to 1;
	char mask = (1 << (n & 7));

	buf[n >> 3] |= mask;
}

void resetNthBit(char *buf, int64_t n) {
	// Get the corresponding byte and bitwise-and it to max the correct bit to 1;
	char mask = 255 ^ (1 << (n & 7));
	
	buf[n >> 3] = buf[n >> 3] & mask;
}

void toggleNthBit(char *buf, int64_t n) {
	// Get the corresponding byte and bitwise-xor it to toggle the correct bit to 1;
	char mask = (1 << (n & 7));
	
	buf[n >> 3] ^= mask;
}