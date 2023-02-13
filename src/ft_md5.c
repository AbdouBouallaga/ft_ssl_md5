#include "../inc/ft_ssl.h"

extern struct flags g_flags;

u_int32_t A0;
u_int32_t B0;
u_int32_t C0;
u_int32_t D0;

u_int32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
                   0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
                   0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
                   0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
                   0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9,
                   0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
                   0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
                   0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235,
                   0x2ad7d2bb, 0xeb86d391};


int s(i)
{
    int a[4] = {7, 12, 17, 22};
    int b[4] = {5, 9, 14, 20};
    int c[4] = {4, 11, 16, 23};
    int d[4] = {6, 10, 15, 21};
    int *x = NULL;
    if (i < 16)
        x = a;
    else if (i > 15 && i < 32)
        x = b;
    else if (i > 31 && i < 48)
        x = c;
    else if (i > 47 && i < 64)
        x = d;

    return (x[i % 4]);
}

static void process(u_int32_t *M)
{
    u_int32_t A = A0;
    u_int32_t B = B0;
    u_int32_t C = C0;
    u_int32_t D = D0;
    u_int8_t i = -1;
    
    while (++i < 64)
    {
        u_int32_t F, g = 0;
        if (i < 16)
        {
            // F = (((B) & (C)) | ((~B) & (D)));
            F = (D ^ (B & (C ^ D)));
            g = i;
        }

        if (i > 15 && i <= 31)
        {
            // F = (((D) & (B)) | ((~D) & (C)));
            F = (C ^ (D & (B ^ C)));
            g = ((5 * i) + 1) % 16;
        }

        if (i > 31 && i <= 47)
        {
            F = ((B) ^ (C) ^ (D));
            g = ((3 * i) + 5) % 16;
        }

        if (i > 47)
        {
            F = ((C) ^ ((B) | (~D)));
            g = (7 * i) % 16;
        }

        F = F + A + (u_int32_t)K[i] + (u_int32_t)M[g];
        A = D;
        D = C;
        C = B;
        B = B + ROTL((F), (s(i)));

    }
    A0 += A;
    B0 += B;
    C0 += C;
    D0 += D;
}

int md5(char *str, char *title)
{
    unsigned long long len;
    unsigned long long messageBits;
    unsigned long long messageBits_bak;
    char *buffer;
    unsigned int i;
    int p;
    int j;
    int bit;
    int rep;
    unsigned int newlen;
    u_int64_t pow;
    u_int32_t m[16];
    u_int32_t ptr;

    A0 = 0x67452301;
    B0 = 0xefcdab89;
    C0 = 0x98badcfe;
    D0 = 0x10325476;

    len = ft_strlen(str);

    messageBits = len * 8;
    messageBits_bak = messageBits;

    newlen = len;
    while (newlen % 64 != 56)
    {
        newlen++;
    }
    messageBits = newlen * 8;
    buffer = (char *)malloc(sizeof(char) * newlen + (8));
    if (buffer == NULL)
    {
        printf("Error: malloc failed");
        return 1;
    }
    ft_bzero(buffer, newlen + 8);
    ft_memcpy(buffer, str, len);
    buffer[len] = 0x80; // 10000000

    i = 0;   // count the bits
    p = 63;  // navigate through the 64 bits value
    j = 0;   // navigate through the buffer blocks
    bit = 8; // set the bits in the buffer blocks
    while (1)
    { // set the 64 bits value of len in bits
        pow = power(2, p);
        if (pow <= messageBits_bak)
        {
            buffer[newlen + 7 - j] = buffer[newlen + 7 - j] | (1 << bit); // set the bit in the buffer to 1
            messageBits_bak -= pow;                                       // subtract the value of the bit from the messageBits
        }
        i++;
        if (i == 8)
        {
            i = 0;
            bit = 8;
            j++;
        }
        p--;
        bit--;
        if (p == -1)
            break;
    }
    if (g_flags.verbose)
        displaybits(buffer, newlen + 8, "HERE IS THE BUFFER");

    i = 0;
    j = 0;
    while (i < newlen + 8)
    {
        j = -1;
        while (++j < 16)
        {
            ft_memcpy(&m[j], buffer + i + (j * 4), 4);
        }
        j = -1;
        if (g_flags.verbose == 1)
            displaybits((char *)m, 16*4, "HERE IS THE CURRENT BLOCK");
        process(m);
        i += 64;
    }

    if (!g_flags.q && !g_flags.p && !g_flags.r)
    { // no flags
        write(1, "MD5(", 4);
        write(1, title, ft_strlen(title));
        write(1, ")= ", 4);
    }
    if (g_flags.p && g_flags.Stdin)
    { // -p
        write(1, title, ft_strlen(title));
        write(1, "\n", 1);
        g_flags.p = 0;
    }
    rep = 0;
    ptr = A0;
    while (rep < 16)
    {
        u_int8_t buff = ptr & 0xff;
        hex_dump(buff);
        ptr = ptr >> 8;
        rep++;
        if (rep % 4 == 0)
        {
            if (rep == 4)
                ptr = B0;
            if (rep == 8)
                ptr = C0;
            if (rep == 12)
                ptr = D0;
        }
    }
    if (g_flags.r && !g_flags.q && !g_flags.Stdin)
    {
        write(1, " ", 1);
        write(1, title, ft_strlen(title));
    }
    if (g_flags.Stdin)
        g_flags.Stdin = 0;
    write(1, "\n", 1);
    free(buffer);
    return (0);
}
