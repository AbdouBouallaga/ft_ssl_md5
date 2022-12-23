#ifndef FT_SSL_H
#define FT_SSL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <libkern/OSByteOrder.h>

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

struct flags
{
    int algo;
    int p;
    int q;
    int r;
};

void                displaybits(char *x, unsigned int len);
unsigned long long  power(int i, int j);
int                 md5(char *str, char *title);
int                 sha256(char *str, char *title);
void                hex_dump(int ch);

#endif