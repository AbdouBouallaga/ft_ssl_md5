#include "../inc/ft_ssl.h"

void displaybits(char *x, unsigned int len, char *msg)
{
    unsigned int i;
    int j;
    unsigned int jump;

    if (msg)
    {
        ft_putstr(msg);
        ft_putchar('\n');
    }
    i = 0;
    j = 0;
    jump = 0;
    while (i < len)
    {
        j = 7;
        while (1)
        {
            if (x[i] & (1 << j))
                ft_putnbr(1);
            else
                ft_putnbr(0);
            j--;
            if (j == -1)
            {
                jump++;
                break;
            }
        }
        i++;
        if (jump == 4)
        {
            ft_putchar('\n');
            jump = 0;
        }
        else
            ft_putchar(' ');
    }
    ft_putchar('\n');
}

void displaywords(u_int32_t *x, unsigned int len, char *msg)
{
    unsigned int i;
    int j;
    unsigned int K;
    unsigned int w;

    i = 0;
    j = 0;
    K = 0;
    w = 0;
    if (msg)
    {
        ft_putstr(msg);
        ft_putchar('\n');
    }
    printf("w%2d ", w);
    while (i < len)
    {
        j = 31;
        while (1)
        {
            if (x[i] & (1 << j))
                printf("1");
            else
                printf("0");
            j--;
            if (j == -1)
            {
                K++;
                break;
            }
        }
        i++;
        if (K)
        {
            w++;
            printf("\n");
            if (w < len)
                printf("w%2d ", w);
            K = 0;
        }
    }
    printf("\n");
}

unsigned long long power(int i, int j)
{
    unsigned long long result;

    result = 1;
    while (j > 0)
    {
        result *= i;
        j--;
    }
    return (result);
}

void hex_dump(int ch)
{
    int a = ch / 16;
    int i = -1;
    while (++i < 2)
    {
        if (a < 10)
            a = '0' + a;
        else
            a = 'a' + a - 10;
        write(1, &a, 1);
        a = ch % 16;
    }
}

void halt_and_catch_fire(char *msg)
{
    ft_putstr(msg);
    exit(1);
}

u_int32_t ROTL(u_int32_t x, u_int32_t n)
{
    return ((x) << (n) | ((x) >> (32 - (n))));
}

u_int32_t ROTR(u_int32_t x, u_int32_t n)
{
    return ((x) >> (n) | ((x) << (32 - (n))));
}