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
    // declare MD5 constants
    u_int32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,\
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,\
    0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,\
    0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,\
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9,\
    0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,\
    0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,\
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235,\
    0x2ad7d2bb, 0xeb86d391};
    // u_int32_t K1 = 0xd76aa478;
    // u_int32_t K2 = 0xe8c7b756;
    // u_int32_t K3 = 0x242070db;
    // u_int32_t K4 = 0xc1bdceee;
    // u_int32_t K5 = 0xf57c0faf;
    // u_int32_t K6 = 0x4787c62a;
    // u_int32_t K7 = 0xa8304613;
    // u_int32_t K8 = 0xfd469501;
    // u_int32_t K9 = 0x698098d8;
    // u_int32_t K10 = 0x8b44f7af;
    // u_int32_t K11 = 0xffff5bb1;
    // u_int32_t K12 = 0x895cd7be;
    // u_int32_t K13 = 0x6b901122;
    // u_int32_t K14 = 0xfd987193;
    // u_int32_t K15 = 0xa679438e;
    // u_int32_t K16 = 0x49b40821;
    // u_int32_t K17 = 0xf61e2562;
    // u_int32_t K18 = 0xc040b340;
    // u_int32_t K19 = 0x265e5a51;
    // u_int32_t K20 = 0xe9b6c7aa;
    // u_int32_t K21 = 0xd62f105d;
    // u_int32_t K22 = 0x02441453;
    // u_int32_t K23 = 0xd8a1e681;
    // u_int32_t K24 = 0xe7d3fbc8;
    // u_int32_t K25 = 0x21e1cde6;
    // u_int32_t K26 = 0xc33707d6;
    // u_int32_t K27 = 0xf4d50d87;
    // u_int32_t K28 = 0x455a14ed;
    // u_int32_t K29 = 0xa9e3e905;
    // u_int32_t K30 = 0xfcefa3f8;
    // u_int32_t K31 = 0x676f02d9;
    // u_int32_t K32 = 0x8d2a4c8a;
    // u_int32_t K33 = 0xfffa3942;
    // u_int32_t K34 = 0x8771f681;
    // u_int32_t K35 = 0x6d9d6122;
    // u_int32_t K36 = 0xfde5380c;
    // u_int32_t K37 = 0xa4beea44;
    // u_int32_t K38 = 0x4bdecfa9;
    // u_int32_t K39 = 0xf6bb4b60;
    // u_int32_t K40 = 0xbebfbc70;
    // u_int32_t K41 = 0x289b7ec6;
    // u_int32_t K42 = 0xeaa127fa;
    // u_int32_t K43 = 0xd4ef3085;
    // u_int32_t K44 = 0x04881d05;
    // u_int32_t K45 = 0xd9d4d039;
    // u_int32_t K46 = 0xe6db99e5;
    // u_int32_t K47 = 0x1fa27cf8;
    // u_int32_t K48 = 0xc4ac5665;
    // u_int32_t K49 = 0xf4292244;
    // u_int32_t K50 = 0x432aff97;
    // u_int32_t K51 = 0xab9423a7;
    // u_int32_t K52 = 0xfc93a039;
    // u_int32_t K53 = 0x655b59c3;
    // u_int32_t K54 = 0x8f0ccc92;
    // u_int32_t K55 = 0xffeff47d;
    // u_int32_t K56 = 0x85845dd1;
    // u_int32_t K57 = 0x6fa87e4f;
    // u_int32_t K58 = 0xfe2ce6e0;
    // u_int32_t K59 = 0xa3014314;
    // u_int32_t K60 = 0x4e0811a1;
    // u_int32_t K61 = 0xf7537e82;
    // u_int32_t K62 = 0xbd3af235;
    // u_int32_t K63 = 0x2ad7d2bb;
    // u_int32_t K64 = 0xeb86d391;
    // Initialize variables
    u_int32_t a0 = 0x67452301;
    u_int32_t b0 = 0xefcdab89;
    u_int32_t c0 = 0x98badcfe;
    u_int32_t d0 = 0x10325476;
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
    // while(){

    // }
    return(0);
}




int main(int ac, char **av)
{
    if (ac == 2){
        md5(av[1]);
    }
    return(0);
} 