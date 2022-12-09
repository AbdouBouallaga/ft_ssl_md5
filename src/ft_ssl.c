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
    // Append padding bits and Append length
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
    printf("64 bit l: \n");
    // ft_memcpy(buffer+newlen, *len, 8);

    int i = 0; // count the bits
    int p = 63; // navigate through the 64 bits value
    int j = 0; // navigate through the buffer blocks
    int bit = 8; // set the bits in the buffer blocks
    while (1){
        // printf("2^%d: %llu\n",p, pow(2,p));
        if(pow(2,p) <= messageBits_bak){
            // printf("1 | ");
            buffer[newlen+j] = buffer[newlen+j]|(1<<bit); // set the bit in the buffer to 1
            messageBits_bak -= pow(2,p); // subtract the value of the bit from the messageBits
            // len -= pow(2,p);
        }
        // else{
        //     printf("0 | ");
        // }
        // printf("j = %d, bit = %d\n",j,bit);
        i++;
        if (i == 8){
            // printf("\n");
            i = 0;
            bit = 8;
            j++;
        }
        p--;
        bit--;
        if (p == -1)
            break;
    }
    printf("\n");
    printf("\n");
    buffer[len] = 0x80;
    printf("newmessageBits: %llu\n",messageBits);
    displaybits(buffer, newlen+8);
    // Initialize MD Buffer
    u_int32_t a0 = 0x67452301;
    u_int32_t b0 = 0xefcdab89;
    u_int32_t c0 = 0x98badcfe;
    u_int32_t d0 = 0x10325476;
    // Process message in 512 bit (16-word) blocks
    printf("\n");

    i = 0;
    j = 0;
    u_int32_t *m[16];
    while(i < newlen+8){
        ft_memcpy(&m[j], &buffer[i], 4);
        m[j] = &buffer[i];
        displaybits(m[j], 4);
        i+=4;
        j++;
        if (j == 4){
            printf("\ni = %d\n",i);
            j = 0;
        }
    } 
    return(0);
}




int main(int ac, char **av)
{
    if (ac == 2){
        md5(av[1]);
    }
    return(0);
} 