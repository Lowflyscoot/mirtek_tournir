#include <stdlib.h>

unsigned long gen_crc(unsigned char *p, size_t n);
void make_crc_table(unsigned long crcTable[]);