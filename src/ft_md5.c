#include "../inc/ft_ssl.h"

u_int32_t A0 = 0x67452301;
u_int32_t B0 = 0xefcdab89;
u_int32_t C0 = 0x98badcfe;
u_int32_t D0 = 0x10325476;

u_int32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,\
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,\
    0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,\
    0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,\
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9,\
    0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,\
    0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,\
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235,\
    0x2ad7d2bb, 0xeb86d391};

// From https://opensource.apple.com/source/ppp/ppp-37/ppp/pppd/md5.c.auto.html //
/* F, G, H and I are basic MD5 functions */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// #ifdef __STDC__
// #define UL(x)	x##U
// #else
#define UL(x)	x
// #endif

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define FF(a, b, c, d, x, s, ac) \
  {(a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) \
  {(a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) \
  {(a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) \
  {(a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
// end //
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

int s(i){
    int a[4] = {7, 12, 17, 22};
    int b[4] = {5,  9, 14, 20};
    int c[4] = {4, 11, 16, 23};
    int d[4] = {6, 10, 15, 21};
    int *x;
    if (i < 16)
        x = a;
    else if (i > 15 && i < 32)
        x = b;
    else if (i > 31 && i < 48)
        x = c;
    else if (i > 47 && i < 64)
        x = d;
    // printf("i = %d; i\%4 = %d; x[%d] = %d\n", i, i%4, i%4, x[i%4]);
    return(x[i%4]);
}

void process(u_int32_t *M)
{
    u_int32_t A = A0;
    u_int32_t B = B0;
    u_int32_t C = C0;
    u_int32_t D = D0;

    u_int8_t i = -1;
    u_int8_t deb = 0;
    while(++i < 64){
        u_int32_t F,g = 0;
        // ( 0 ≤ i ≤ 15): F := D xor (B and (C xor D))
        if (i < 16){
            // F = (((B) & (C)) | ((~B) & (D)));
            F = (D ^ (B & (C ^ D)));
            g = i;
        }
        if (i == 15){
            deb=1;
        }
        if (i > 15 && i <= 31){
            // (16 ≤ i ≤ 31): F := C xor (D and (B xor C))
            // F = (((D) & (B)) | ((~D) & (C)));
            F = (C ^ (D & (B ^ C)));
            g = ((5*i)+1) % 16;
        }
        if (i == 31){
            deb=1;
        }
        if (i > 31 && i <= 47){
            F = ((B) ^ (C) ^ (D));
            g = ((3*i)+ 5) % 16;
        }
        if (i == 47){
            deb=1;
        }
        if (i > 47) {
            F = ((C) ^ ((B) | (~D)));
            g = (7*i) % 16;
        }
        if (i == 63){
            deb = 1;
        }
        F = F + A + (u_int32_t)K[i] + (u_int32_t)M[g];
        A = D;
        D = C;
        C = B;
        B = B + ROTATE_LEFT((F),(s(i)));
        if (deb){
            printf("A: %d\n", A);
            printf("B: %d\n", B);
            printf("C: %d\n", C);
            printf("D: %d\n", D);
            printf("\n");
            deb = 0;
        }
    }
    A0 += A;
    B0 += B;
    C0 += C;
    D0 += D;
    // printf("Hash value: %08x%08x%08x%08x\n", A, B, C, D);
    // printf("Hash value: %08x%08x%08x%08x\n", A0, B0, C0, D0);

}

int md5(char *str)
{
    // declare MD5 constants
    // Initialize hash value
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
    // displaybits((char *)str, len);
    unsigned int newlen = len;
    while (newlen % 64 != 56)
    {
        newlen++;
    }
    printf("newlen: %d\n",newlen);
    messageBits = newlen * 8;
    char *buffer = (char *)malloc(sizeof(char) * newlen+(8));
    if (buffer == NULL)
    {
        printf("Error: malloc failed");
        return 1;
    }
    ft_bzero(buffer, newlen);
    ft_memcpy(buffer, str, len);
    // printf(">>>> %s \n", buffer);
    // printf("64 bit l: \n");
    // ft_memcpy(buffer+newlen, *len, 8);

    int i = 0; // count the bits
    int p = 63; // navigate through the 64 bits value
    int j = 0; // navigate through the buffer blocks
    int bit = 8; // set the bits in the buffer blocks
    u_int64_t pow;
    while (0){
        // printf("2^%d: %llu\n",p, pow(2,p));
        pow = power(2,p);
        if(pow <= messageBits_bak){
            // printf("1 | ");
            buffer[newlen+j] = buffer[newlen+j]|(1<<bit); // set the bit in the buffer to 1
            messageBits_bak -= pow; // subtract the value of the bit from the messageBits
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
    buffer[len+1] = '\0';
    printf("%s\n",buffer);
    buffer[newlen+7] = (u_int64_t)messageBits;
    printf("\n");
    displaybits(&buffer[newlen], 8);
    printf("\n");
    // printf("newmessageBits: %llu\n",messageBits);
    displaybits(buffer, newlen+8); 
    // Process message in 512 bit (16-word) blocks
    printf("\n");
    // u_int32_t *m = (u_int32_t)malloc(sizeof(u_int32_t) * 16);
    u_int32_t m[16];
    i = 0;
    j = 0;
    int copy;
    int a,b;
    while(i < newlen+8){
        j = -1;
        while (++j < 16){
            // m[j] = buffer[i+(j*4)];
            ft_memcpy(&m[j], buffer+i+(j*4), 4);
        }
        j = -1;
        while (++j < 16){
            printf("%08x ", m[j]);
        }
        printf("\n");
        process(m);
        i+=64;
    }
    printf("\n\n");
    // print the hash value
    printf("Hash value: %08x%08x%08x%08x\n", A0, B0, C0, D0);
    // printf("Hash value: %08x%08x%08x%08x\n", aa, bb, cc, dd);
    return(0);
}
