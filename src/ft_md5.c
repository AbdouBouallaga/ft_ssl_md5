#include "../inc/ft_ssl.h"

// From https://opensource.apple.com/source/ppp/ppp-37/ppp/pppd/md5.c.auto.html //
/* F, G, H and I are basic MD5 functions */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#ifdef __STDC__
#define UL(x)	x##U
#else
#define UL(x)	x
#endif

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

void process(u_int32_t *aa, u_int32_t *bb, u_int32_t *cc, u_int32_t *dd, u_int32_t *in, u_int32_t *k)
{
    u_int32_t a = *aa;
    u_int32_t b = *bb;
    u_int32_t c = *cc;
    u_int32_t d = *dd;

    // int i = 0;
    // while (i < 16){
    //     x[i] = OSSwapLittleToHostInt32(x[i]);
    //     i++;
    // }
    // i = 0;
    // while (i < 64){
    //     k[i] = OSSwapLittleToHostInt32(k[i]);
    //     i++;
    // }
    // int i = 0;
    // while (i < 16){
    //     x[i] = OSSwapBigToHostInt32(x[i]);
    //     i++;
    // }
    // i = 0;
    // while (i < 64){
    //     k[i] = OSSwapBigToHostInt32(k[i]);
    //     i++;
    // }
    // //Round 1
    // FF(a, b, c, d, x[0],  7,  k[0]);
    // FF(d, a, b, c, x[1],  12, k[1]);
    // FF(c, d, a, b, x[2],  17, k[2]);
    // FF(b, c, d, a, x[3],  22, k[3]);
    // FF(a, b, c, d, x[4],  7,  k[4]);
    // FF(d, a, b, c, x[5],  12, k[5]);
    // FF(c, d, a, b, x[6],  17, k[6]);
    // FF(b, c, d, a, x[7],  22, k[7]);
    // FF(a, b, c, d, x[8],  7,  k[8]);
    // FF(d, a, b, c, x[9],  12, k[9]);
    // FF(c, d, a, b, x[10], 17, k[10]);
    // FF(b, c, d, a, x[11], 22, k[11]);
    // FF(a, b, c, d, x[12], 7,  k[12]);
    // FF(d, a, b, c, x[13], 12, k[13]);
    // FF(c, d, a, b, x[14], 17, k[14]);
    // FF(b, c, d, a, x[15], 22, k[15]);
  
    // //Round 2
    // GG(a, b, c, d, x[1],  5,  k[16]);
    // GG(d, a, b, c, x[6],  9,  k[17]);
    // GG(c, d, a, b, x[11], 14, k[18]);
    // GG(b, c, d, a, x[0],  20, k[19]);
    // GG(a, b, c, d, x[5],  5,  k[20]);
    // GG(d, a, b, c, x[10], 9,  k[21]);
    // GG(c, d, a, b, x[15], 14, k[22]);
    // GG(b, c, d, a, x[4],  20, k[23]);
    // GG(a, b, c, d, x[9],  5,  k[24]);
    // GG(d, a, b, c, x[14], 9,  k[25]);
    // GG(c, d, a, b, x[3],  14, k[26]);
    // GG(b, c, d, a, x[8],  20, k[27]);
    // GG(a, b, c, d, x[13], 5,  k[28]);
    // GG(d, a, b, c, x[2],  9,  k[29]);
    // GG(c, d, a, b, x[7],  14, k[30]);
    // GG(b, c, d, a, x[12], 20, k[31]);
  
    // //Round 3
    // HH(a, b, c, d, x[5],  4,  k[32]);
    // HH(d, a, b, c, x[8],  11, k[33]);
    // HH(c, d, a, b, x[11], 16, k[34]);
    // HH(b, c, d, a, x[14], 23, k[35]);
    // HH(a, b, c, d, x[1],  4,  k[36]);
    // HH(d, a, b, c, x[4],  11, k[37]);
    // HH(c, d, a, b, x[7],  16, k[38]);
    // HH(b, c, d, a, x[10], 23, k[39]);
    // HH(a, b, c, d, x[13], 4,  k[40]);
    // HH(d, a, b, c, x[0],  11, k[41]);
    // HH(c, d, a, b, x[3],  16, k[42]);
    // HH(b, c, d, a, x[6],  23, k[43]);
    // HH(a, b, c, d, x[9],  4,  k[44]);
    // HH(d, a, b, c, x[12], 11, k[45]);
    // HH(c, d, a, b, x[15], 16, k[46]);
    // HH(b, c, d, a, x[2],  23, k[47]);
  
    // //Round 4
    // II(a, b, c, d, x[0],  6,  k[48]);
    // II(d, a, b, c, x[7],  10, k[49]);
    // II(c, d, a, b, x[14], 15, k[50]);
    // II(b, c, d, a, x[5],  21, k[51]);
    // II(a, b, c, d, x[12], 6,  k[52]);
    // II(d, a, b, c, x[3],  10, k[53]);
    // II(c, d, a, b, x[10], 15, k[54]);
    // II(b, c, d, a, x[1],  21, k[55]);
    // II(a, b, c, d, x[8],  6,  k[56]);
    // II(d, a, b, c, x[15], 10, k[57]);
    // II(c, d, a, b, x[6],  15, k[58]);
    // II(b, c, d, a, x[13], 21, k[59]);
    // II(a, b, c, d, x[4],  6,  k[60]);
    // II(d, a, b, c, x[11], 10, k[61]);
    // II(c, d, a, b, x[2],  15, k[62]);
    // II(b, c, d, a, x[9],  21, k[63]);

      /* Round 1 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
  FF ( a, b, c, d, in[ 0], S11, UL(3614090360)); /* 1 */
  FF ( d, a, b, c, in[ 1], S12, UL(3905402710)); /* 2 */
  FF ( c, d, a, b, in[ 2], S13, UL( 606105819)); /* 3 */
  FF ( b, c, d, a, in[ 3], S14, UL(3250441966)); /* 4 */
  FF ( a, b, c, d, in[ 4], S11, UL(4118548399)); /* 5 */
  FF ( d, a, b, c, in[ 5], S12, UL(1200080426)); /* 6 */
  FF ( c, d, a, b, in[ 6], S13, UL(2821735955)); /* 7 */
  FF ( b, c, d, a, in[ 7], S14, UL(4249261313)); /* 8 */
  FF ( a, b, c, d, in[ 8], S11, UL(1770035416)); /* 9 */
  FF ( d, a, b, c, in[ 9], S12, UL(2336552879)); /* 10 */
  FF ( c, d, a, b, in[10], S13, UL(4294925233)); /* 11 */
  FF ( b, c, d, a, in[11], S14, UL(2304563134)); /* 12 */
  FF ( a, b, c, d, in[12], S11, UL(1804603682)); /* 13 */
  FF ( d, a, b, c, in[13], S12, UL(4254626195)); /* 14 */
  FF ( c, d, a, b, in[14], S13, UL(2792965006)); /* 15 */
  FF ( b, c, d, a, in[15], S14, UL(1236535329)); /* 16 */

  /* Round 2 */
#define S21 5
#define S22 9
#define S23 14
#define S24 20
  GG ( a, b, c, d, in[ 1], S21, UL(4129170786)); /* 17 */
  GG ( d, a, b, c, in[ 6], S22, UL(3225465664)); /* 18 */
  GG ( c, d, a, b, in[11], S23, UL( 643717713)); /* 19 */
  GG ( b, c, d, a, in[ 0], S24, UL(3921069994)); /* 20 */
  GG ( a, b, c, d, in[ 5], S21, UL(3593408605)); /* 21 */
  GG ( d, a, b, c, in[10], S22, UL(  38016083)); /* 22 */
  GG ( c, d, a, b, in[15], S23, UL(3634488961)); /* 23 */
  GG ( b, c, d, a, in[ 4], S24, UL(3889429448)); /* 24 */
  GG ( a, b, c, d, in[ 9], S21, UL( 568446438)); /* 25 */
  GG ( d, a, b, c, in[14], S22, UL(3275163606)); /* 26 */
  GG ( c, d, a, b, in[ 3], S23, UL(4107603335)); /* 27 */
  GG ( b, c, d, a, in[ 8], S24, UL(1163531501)); /* 28 */
  GG ( a, b, c, d, in[13], S21, UL(2850285829)); /* 29 */
  GG ( d, a, b, c, in[ 2], S22, UL(4243563512)); /* 30 */
  GG ( c, d, a, b, in[ 7], S23, UL(1735328473)); /* 31 */
  GG ( b, c, d, a, in[12], S24, UL(2368359562)); /* 32 */

  /* Round 3 */
#define S31 4
#define S32 11
#define S33 16
#define S34 23
  HH ( a, b, c, d, in[ 5], S31, UL(4294588738)); /* 33 */
  HH ( d, a, b, c, in[ 8], S32, UL(2272392833)); /* 34 */
  HH ( c, d, a, b, in[11], S33, UL(1839030562)); /* 35 */
  HH ( b, c, d, a, in[14], S34, UL(4259657740)); /* 36 */
  HH ( a, b, c, d, in[ 1], S31, UL(2763975236)); /* 37 */
  HH ( d, a, b, c, in[ 4], S32, UL(1272893353)); /* 38 */
  HH ( c, d, a, b, in[ 7], S33, UL(4139469664)); /* 39 */
  HH ( b, c, d, a, in[10], S34, UL(3200236656)); /* 40 */
  HH ( a, b, c, d, in[13], S31, UL( 681279174)); /* 41 */
  HH ( d, a, b, c, in[ 0], S32, UL(3936430074)); /* 42 */
  HH ( c, d, a, b, in[ 3], S33, UL(3572445317)); /* 43 */
  HH ( b, c, d, a, in[ 6], S34, UL(  76029189)); /* 44 */
  HH ( a, b, c, d, in[ 9], S31, UL(3654602809)); /* 45 */
  HH ( d, a, b, c, in[12], S32, UL(3873151461)); /* 46 */
  HH ( c, d, a, b, in[15], S33, UL( 530742520)); /* 47 */
  HH ( b, c, d, a, in[ 2], S34, UL(3299628645)); /* 48 */

  /* Round 4 */
#define S41 6
#define S42 10
#define S43 15
#define S44 21
  II ( a, b, c, d, in[ 0], S41, UL(4096336452)); /* 49 */
  II ( d, a, b, c, in[ 7], S42, UL(1126891415)); /* 50 */
  II ( c, d, a, b, in[14], S43, UL(2878612391)); /* 51 */
  II ( b, c, d, a, in[ 5], S44, UL(4237533241)); /* 52 */
  II ( a, b, c, d, in[12], S41, UL(1700485571)); /* 53 */
  II ( d, a, b, c, in[ 3], S42, UL(2399980690)); /* 54 */
  II ( c, d, a, b, in[10], S43, UL(4293915773)); /* 55 */
  II ( b, c, d, a, in[ 1], S44, UL(2240044497)); /* 56 */
  II ( a, b, c, d, in[ 8], S41, UL(1873313359)); /* 57 */
  II ( d, a, b, c, in[15], S42, UL(4264355552)); /* 58 */
  II ( c, d, a, b, in[ 6], S43, UL(2734768916)); /* 59 */
  II ( b, c, d, a, in[13], S44, UL(1309151649)); /* 60 */
  II ( a, b, c, d, in[ 4], S41, UL(4149444226)); /* 61 */
  II ( d, a, b, c, in[11], S42, UL(3174756917)); /* 62 */
  II ( c, d, a, b, in[ 2], S43, UL( 718787259)); /* 63 */
  II ( b, c, d, a, in[ 9], S44, UL(3951481745)); /* 64 */

    //add this chunk's hash to result so far
    *aa += a;
    *bb += b;
    *cc += c;
    *dd += d;
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
    // Initialize chaining variables
    u_int32_t A = 0x67452301;
    u_int32_t B = 0xefcdab89;
    u_int32_t C = 0x98badcfe;
    u_int32_t D = 0x10325476;
    printf("A: %x\nB: %x\nC: %x\nD: %x\n",A,B,C,D);
    // Initialize hash value
    u_int32_t aa = A;
    u_int32_t bb = B;
    u_int32_t cc = C;
    u_int32_t dd = D;
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
    char *buffer = (char *)malloc(sizeof(char) * newlen+(64/8));
    if (buffer == NULL)
    {
        printf("Error: malloc failed");
        return 1;
    }
    bzero(buffer, newlen);
    memcpy(buffer, str, len);
    // printf(">>>> %s \n", buffer);
    // printf("64 bit l: \n");
    // ft_memcpy(buffer+newlen, *len, 8);

    int i = 0; // count the bits
    int p = 63; // navigate through the 64 bits value
    int j = 0; // navigate through the buffer blocks
    int bit = 8; // set the bits in the buffer blocks
    while (1){
        // printf("2^%d: %llu\n",p, pow(2,p));
        if(power(2,p) <= messageBits_bak){
            // printf("1 | ");
            buffer[newlen+j] = buffer[newlen+j]|(1<<bit); // set the bit in the buffer to 1
            messageBits_bak -= power(2,p); // subtract the value of the bit from the messageBits
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
        process(&aa, &bb, &cc, &dd, m, K);
        i+=64;
    }
    printf("\n\n");
    // print the hash value
    printf("Hash value: %08x%08x%08x%08x\n", aa+A, bb+B, cc+C, dd+D);
    printf("Hash value: %08x%08x%08x%08x\n", aa, bb, cc, dd);
    return(0);
}
