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

unsigned long long pow(int i, int j)
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

int md5(char *str)
{
    // unsigned int len;
    unsigned long long len;
    unsigned long long temp;
    // u_int64_t len;
    unsigned long long messageBits;
    unsigned long long messageBits_bak;


    len = ft_strlen(str);
    printf("len: %llu\n",len);
    messageBits = len * 8;
    messageBits_bak = messageBits;
    printf("messageBits: %llu\n",messageBits);
    displaybits((char *)str, len);
    unsigned int newlen = len;
    while (newlen % 64 != 56)
    {
        newlen++;
    }
    printf("newlen: %d\n",newlen);
    messageBits = newlen * 8;
    char *buffer = (char *)malloc(sizeof(char) * newlen+(64/8));
    ft_bzero(buffer, newlen);
    ft_memcpy(buffer, str, len);
    // ft_memcpy(buffer+newlen, *len, 8);
    int i = 0;
    int j = 0;
    int p = 63;
    while (1){
        // printf("2^%d: %llu\n",p, pow(2,p));
        if(pow(2,p) == messageBits_bak){
            printf("1");
            buffer[newlen+j] = buffer[newlen+j]|(1<<p);
            // len -= pow(2,p);
        }
        else{
            printf("0");
        }
        i++;
        if (i == 8){
            printf(" ");
            i = 0;
            j++;
        }
        p--;
        if (p == -1)
            break;
    }
    printf("\n");
    printf("\n");
    buffer[len] = 0x80;
    printf("newmessageBits: %llu\n",messageBits);
    displaybits(buffer, newlen+8);
    return(0);
}




int main(int ac, char **av)
{
    if (ac == 2){
        md5(av[1]);
    }
    return(0);
} 