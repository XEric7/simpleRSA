#include "tool.h"

// C program of finding modulo multiplication
#include <stdio.h>

// Returns (a * b) % mod
bignum moduloMultiplication(bignum a, bignum b, bignum mod)
{
    bignum res = 0; // Initialize result

    // Update a if it is more than
    // or equal to mod
    a %= mod;

    while (b)
    {
        // If b is odd, add a with result
        if (b & 1)
            res = (res + a) % mod;

        // Here we assume that doing 2*a
        // doesn't cause overflow
        a = (2 * a) % mod;

        b >>= 1; // b = b / 2
    }

    return res;
}

bignum powMod(bignum base, bignum index, bignum mod)
{
    bignum res = 1; // Initialize result

    while (index > 0)
    {
        // If index is odd, multiply base with result
        if (index & 1u)
            res = moduloMultiplication(res, base, mod);

        // index must be even now
        index = index >> 1;           // index = index/2
        base = moduloMultiplication(base, base, mod); // Change base to base^2%mod
    }
    return (res % mod);
}

// generate unsigned __int64 random number
unsigned __int64 uint64Rand()
{
    ASSERT((0x7FFF == RAND_MAX))
    unsigned __int64 r = 0;

    for (int i = 0; i < 5; ++i)
    {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}


unsigned __int128 uint128Rand()
{
    ASSERT((0x7FFF == RAND_MAX))
    bignum r = 0;

    for (int i = 0; i < 9; ++i)
    {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    __int128 allone = 0;
    allone--;
    return r & allone;
}

// n为大于3的数
bool isprime(bignum n)
{
    ASSERT((n > 3))

    if (n % 2 == 0)
    {
        return false;
    }

    // n-1 = 2^k * m
    int k = 0;
    bignum m = n - 1;
    for (; m % 2 == 0; m /= 2)
    {
        k++;
    }
    // 使用 Miller-Rabin算法
    for (int i = 0; i < 100; i++)
    {
        bignum a = uint128Rand() % (n - 2) + 2;
        bignum b = powMod(a, m, n);
        if (b == 1)
        {
            continue;
        }
        for (int i = 0; i < k; i++)
        {
            if (b == n - 1)
            {
                goto ENDMillerRabin;
            }
            else
            {
                b = powMod(b, b, n);
            }
        }
        return false;
    ENDMillerRabin:;
    }
    return true;
}

//判断x, y是否互质
bool coprime(bignum x, bignum y)
{
    bignum tmp;

    if (y > x)
    {
        EXCHANGE(x, y, tmp);
    }
    if (x == y || x % y == 0)
    {
        return false;
    }

    while (true)
    {
        x %= y;
        if (y > x)
        {
            EXCHANGE(x, y, tmp);
        }
        if (y == 1)
        {
            return true;
        }
        if (x % y == 0)
        {
            return false;
        }
    }
}

// C program to find multiplicative modulo inverse using
// Extended Euclid algorithm.

// C function for extended Euclidean Algorithm
bignum gcdExtended(bignum a, bignum b, bignum *x, bignum *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    bignum x1, y1; // To store results of recursive call
    bignum gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// Function to find modulo inverse of a
bignum modInverse(bignum a, bignum m)
{
    bignum x, y;
    if (gcdExtended(a, m, &x, &y) != 1)
    {
        printf("Inverse doesn't exist");
        exit(1);
    }

    // m is added to handle negative x
    bignum res = (x % m + m) % m;
    return res;
}


// 将int128类型的整数保存到文件
void int128tofile(unsigned __int128 num, FILE *fp)
{
    if (num == 0)
    {
        fputc('0', fp);
    }
    else
    {
        char c;
        char str[33];
        int i = 0;
        int remain;
        while (num != 0)
        {
            remain = num % 16;
            num /= 16;
            if (remain < 10)
            {
                c = '0' + remain;
            }
            else
            {
                c = 'A' + (remain - 10);
            }
            str[i++] = c;
        }
        while (i > 0)
        {
            fputc(str[--i], fp);
        }
    }
}

//将hex的string转换成 int128
unsigned __int128 stringToInt128(char *str)
{
    unsigned __int128 num = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            num = num * 16 + (str[i] - '0');
        }
        else if ('A' <= str[i] && str[i] <= 'F')
        {
            num = num * 16 + (str[i] - 'A' + 10);
        }
        else if ('a' <= str[i] && str[i] <= 'f')
        {
            num = num * 16 + (str[i] - 'a' + 10);
        }
        else
        {
            printf("Invalid hex string");
            exit(1);
        }
    }
    return num;
}