#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tool.h"

#define MIN_PRIME 10000000000ull
#define MAX_PRIME 100000000000ull

// generate a prime bignum > min
bignum generatePrime(bignum min, bignum max)
{
    bignum result;
    while (true)
    {
        result = uint64Rand() % max;
        if (result > min && isprime(result))
        {
            return result;
        }
    }
}

void generateKey()
{
    bignum p = generatePrime(MIN_PRIME, MAX_PRIME);
    bignum q = generatePrime(MIN_PRIME, MAX_PRIME);
    ASSERT(coprime(p, q))

    bignum n = (bignum)p * q;
    bignum fain = (bignum)(p - 1) * (q - 1);

    // fain 与 e 互素
    bignum e = uint128Rand() % fain;
    while(!coprime(fain, e))
    {
        e = uint128Rand() % fain;
    }
    bignum d = modInverse(e, fain);

    // 写入文件
    FILE *p_txt = fopen("p.txt", "w");
    int128tofile(p, p_txt);
    fclose(p_txt);

    FILE *q_txt = fopen("q.txt", "w");
    int128tofile(q, q_txt);
    fclose(q_txt);

    FILE *n_txt = fopen("n.txt", "w");
    int128tofile(n, n_txt);
    fclose(n_txt);

    FILE *e_txt = fopen("e.txt", "w");
    int128tofile(e, e_txt);
    fclose(e_txt);

    FILE *d_txt = fopen("d.txt", "w");
    int128tofile(d, d_txt);
    fclose(d_txt);
}


int main()
{
    generateKey();
    return 0;
}