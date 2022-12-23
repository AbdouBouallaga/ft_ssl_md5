#include "../inc/ft_ssl.h"

void displaybits(char *x, unsigned int len)
{
    unsigned int i;
    unsigned int j;

    i = 0;
    j = 0;
    while (i < len)
    {
        j = 7;
        while (1)
        {
            if (x[i] & (1 << j))
                printf("1");
            else
                printf("0");
            j--;
            if (j == -1)
                break;
        }
        i++;
        printf(" ");
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

void    hex_dump(int ch)
{
    int a = ch/16;
    int i = -1;
    while (++i < 2){
        if (a < 10)
            a = '0' + a;
        else
            a = 'a' + a - 10;
        write(1, &a, 1);
        a = ch%16;
    }
}