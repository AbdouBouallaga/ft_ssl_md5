#ifndef FT_SSL_H
#define FT_SSL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <libkern/OSByteOrder.h>

void displaybits(char *x, unsigned int len);
unsigned long long power(int i, int j);
void process(u_int32_t *aa, u_int32_t *bb, u_int32_t *cc, u_int32_t *dd, u_int32_t *x, u_int32_t *k);
int md5(char *str);

#endif