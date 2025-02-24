#include "config.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
	((byte) & 0x80 ? '1' : '0'), \
	((byte) & 0x40 ? '1' : '0'), \
	((byte) & 0x20 ? '1' : '0'), \
	((byte) & 0x10 ? '1' : '0'), \
	((byte) & 0x08 ? '1' : '0'), \
	((byte) & 0x04 ? '1' : '0'), \
	((byte) & 0x02 ? '1' : '0'), \
	((byte) & 0x01 ? '1' : '0')

#define getBit(buf, n) \
	(0 != (buf[n >> 5] & (1 << (n & 31))))
#define setBit(buf, n) \
	buf[n >> 5] |= (1 << (n & 31))
#define resetBit(buf, n) \
	buf[n >> 5] &= ~(1 << (n & 31))
#define toggleBit(buf, n) \
	buf[n >> 5] ^= (1 << (n & 31))