#ifndef FT_SSL_H
#define FT_SSL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h> // ceil

// #include <arpa/inet.h> // little to big endian

struct flags
{
    short algo;
    short p;
    short q;
    short r;
    short verbose; // -s
    short Stdin;
};

void                displaybits(char *x, unsigned int len, char *msg);
void                displaywords(u_int32_t *x, unsigned int len, char *msg);
unsigned long long  power(int i, int j);
int                 md5(char *str, char *title);
int                 sha256(char *str, char *title);
void                hex_dump(int ch);
void                halt_and_catch_fire(char *msg);
u_int32_t           ROTL(u_int32_t x, u_int32_t n);
u_int32_t           ROTR(u_int32_t x, u_int32_t n);


#endif