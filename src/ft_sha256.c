#include "../inc/ft_ssl.h"

extern struct flags g_flags;

u_int32_t h0;
u_int32_t h1;
u_int32_t h2;
u_int32_t h3;
u_int32_t h4;
u_int32_t h5;
u_int32_t h6;
u_int32_t h7;

u_int32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// From https://opensource.apple.com/source/ppp/ppp-37/ppp/pppd/md5.c.auto.html //

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
//end of apple code

void displaywords(char *x, unsigned int len)
{
    unsigned int i;
    unsigned int j;
    unsigned int K;
    unsigned int w;


    i = 0;
    j = 0;
    K = 0;
    w = 0;
    len = len * 4;
    printf("w%2d ", w);
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
            if (j == -1){
                K++;
                break;
            }
        }
        i++;
        if (K == 4){
            w++;
            printf("\n");
            if (w < len/4)
                printf("w%2d ", w);
            K = 0;
        }
    }
    printf("\n");
}

unsigned rotr(unsigned x, unsigned n) {
    return (x >> n % 32) | (x << (32-n) % 32);
}

static void process(u_int32_t *w)
{
    u_int32_t a = h0;
    u_int32_t b = h1;
    u_int32_t c = h2;
    u_int32_t d = h3;
    u_int32_t e = h4;
    u_int32_t f = h5;
    u_int32_t g = h6;
    u_int32_t h = h7;

    u_int32_t *test = malloc(sizeof(u_int32_t));

    u_int32_t s0;
    u_int32_t s1;
    u_int32_t S1;
    u_int32_t ch;
    u_int32_t temp1;
    u_int32_t S0;
    u_int32_t maj;
    u_int32_t temp2;

    uint16_t i = 15;
    while (++i < 64){
        test[0] = w[i - 15];
        printf("here\n");
        displaywords(test, 1);
        test[0] = ROTR(test[0], 7);
        displaywords(test, 1);
        printf("\n");
        exit(1);
        s0 = ((ROTR(w[i - 15], 7) ^ (ROTR(w[i-15],18)) ^ (w[i-15] >> 3)));
        s1 = (ROTR(w[i-2],17) ^ ROTR(w[i-2], 19) ^ (w[i-2] >> 10));
        w[i] = w[i-16] + s0 + w[i-7] + s1;
    }
    displaywords((char *)w, 64);
    printf("\n");
    i = -1;
    while (++i < 64){
        S1 = (ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e,25));
        ch = ((e & f) ^ ((~e) & g));
        temp1 = (h1 + S1 + ch + k[i] + w[i]);
        S0 = (ROTR(a,2) ^ ROTR(a,13) ^ ROTR(a,22));
        maj = ((a & b) ^ (a & c) ^ (b & c));
        temp2 = S0 + maj;
        h = g;
        g = f;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
}


int sha256(char *str, char *title)
{
    h0 = 0x6a09e667;
    h1 = 0xbb67ae85;
    h2 = 0x3c6ef372;
    h3 = 0xa54ff53a;
    h4 = 0x510e527f;
    h5 = 0x9b05688c;
    h6 = 0x1f83d9ab;
    h7 = 0x5be0cd19;
    unsigned long long len;
    unsigned long long temp;
    unsigned long long messageBits;
    unsigned long long messageBits_bak;


    len = ft_strlen(str);
    // printf("len: %llu\n",len);
    messageBits = len * 8;
    messageBits_bak = messageBits;
    // printf("messageBits: %llu\n",messageBits);
    // displaybits((char *)str, len);
    unsigned int newlen = len;
    while (newlen % 64 != 56)
    {
        newlen++;
    }
    // printf("newlen: %d\n",newlen);
    messageBits = newlen * 8;
    char *buffer = (char *)malloc(sizeof(char) * newlen+(8));
    if (buffer == NULL)
    {
        printf("Error: malloc failed");
        return 1;
    }
    ft_bzero(buffer, newlen+8);
    ft_memcpy(buffer, str, len);
    buffer[len] = 0x80; // 10000000
    u_int32_t tet = 0x12345678;
    // tet = htonl(tet);
    printf("%x\n", (char)tet);
    int deb = 0;
    while (deb < newlen+8)
    {
        buffer[deb] = htonl(buffer[deb]);
        printf("%x\n", (u_int32_t)buffer[deb]);
        deb+=4;
    }
    // printf(">>>> %s \n", buffer);
    // printf("64 bit l: \n");
    // ft_memcpy(buffer+newlen, *len, 8);

    int i = 0; // count the bits
    int p = 63; // navigate through the 64 bits value
    int j = 0; // navigate through the buffer blocks
    int bit = 8; // set the bits in the buffer blocks
    u_int64_t pow;
    while (1){ // set the 64 bits value of len in bits
        pow = power(2,p);
        if(pow <= messageBits_bak){
            buffer[newlen+j] = buffer[newlen+j]|(1<<bit); // set the bit in the buffer to 1
            messageBits_bak -= pow; // subtract the value of the bit from the messageBits
        }
        i++;
        if (i == 8){
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
    displaybits(buffer, newlen+8);
    // Process message in 512 bit (16-word) blocks
    printf("\n");
    u_int32_t *m = malloc(sizeof(u_int32_t) * 64);
    i = 0;
    j = 0;
    int copy;
    int a,b;
    while(i < newlen+8){
        ft_bzero(m, 64);
        j = -1;
        while (++j < 16){
            // m[j] = buffer[i+(j*4)];
            ft_memcpy(&m[j], buffer+i+(j*4), 4);
        }
        // displaybits((char *)m, 256);
        printf("\n");
        // j = -1;
        // while (++j < 64){
        //     printf("%08x ", m[j]);
        // }
        // printf("\n");
        displaywords((char *)m, 64);
        process(m);
        i+=64;
    }

    if (g_flags.q != 1){
        write(1, "sha256 (", 9);
        write(1, title, ft_strlen(title));
        write(1, ") = ", 5);
    }
    printf("\n%02x%02x%02x%02x",h0&0xff, (h0>>8)&0xff, (h0>>16)&0xff, (h0>>24)&0xff);
    printf("%02x%02x%02x%02x", h1&0xff, (h1>>8)&0xff, (h1>>16)&0xff, (h1>>24)&0xff);
    printf("%02x%02x%02x%02x", h2&0xff, (h2>>8)&0xff, (h2>>16)&0xff, (h2>>24)&0xff);
    printf("%02x%02x%02x%02x", h3&0xff, (h3>>8)&0xff, (h3>>16)&0xff, (h3>>24)&0xff);
    printf("%02x%02x%02x%02x", h4&0xff, (h4>>8)&0xff, (h4>>16)&0xff, (h4>>24)&0xff);
    printf("%02x%02x%02x%02x", h5&0xff, (h5>>8)&0xff, (h5>>16)&0xff, (h5>>24)&0xff);
    printf("%02x%02x%02x%02x", h6&0xff, (h6>>8)&0xff, (h6>>16)&0xff, (h6>>24)&0xff);
    printf("%02x%02x%02x%02x\n", h7&0xff, (h7>>8)&0xff, (h7>>16)&0xff, (h7>>24)&0xff);
    
    // ,A0&0xff, (A0>>8)&0xff, (A0>>16)&0xff, (A0>>24)&0xff);
    int rep = 0;
    u_int32_t ptr = h0;
    while (rep < 32){
        u_int8_t buff = ptr&0xff;
        hex_dump(buff);
        ptr = ptr>>8;
        rep++;
        if (rep % 4 == 0){
            if (rep == 4)
                ptr = h1;
            if (rep == 8)
                ptr = h2;
            if (rep == 12)
                ptr = h3;
            if (rep == 16)
                ptr = h4;
            if (rep == 20)
                ptr = h5;
            if (rep == 24)
                ptr = h6;
            if (rep == 28)
                ptr = h7;
        }
    }
    write(1, "\n", 1);
    // u_int8_t buff = A0&0xff;
    // hex_dump(buff);
    return(0);
}
