#ifndef FT_SSL_H
#define FT_SSL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <libkern/OSByteOrder.h>

struct flags
{
    int algo;
    int p;
    int q;
    int r;
};

void displaybits(char *x, unsigned int len);
unsigned long long power(int i, int j);
void process(u_int32_t *M);
int md5(char *str, char *title);

#endif