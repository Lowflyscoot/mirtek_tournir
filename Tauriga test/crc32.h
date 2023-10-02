#include <stdlib.h>
#include <stdint.h>

uint32_t gen_crc(unsigned char *p, size_t n);
uint32_t crc32c(uint32_t crc, const void *buf, size_t size);
void make_crc_table(unsigned long crcTable[]);
