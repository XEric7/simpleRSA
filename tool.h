#ifndef _tool_h_
#define _tool_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ASSERT(condition)                                                \
    if (!condition)                                                      \
    {                                                                    \
        printf("Assertion failed: line %d file %s", __LINE__, __FILE__); \
        exit(1);                                                         \
    }

#define EXCHANGE(x, y, tmp) \
    tmp = x;                \
    x = y;                  \
    y = tmp;

typedef unsigned __int128 bignum;

bignum powMod(bignum base, bignum index, bignum mod);

// generate unsigned int64 random number
unsigned __int64 uint64Rand();

// generate unsigned int128 random number
unsigned __int128 uint128Rand();

// 判断一个大于3的数是否为素数
bool isprime(bignum n);

// 判断两数是否互质
bool coprime(bignum x, bignum y);


//将int128类型的整数保存到文件
void int128tofile(bignum num, FILE *fp);

//将hex的string转换成 int128
unsigned __int128 stringToInt128(char *str);

// Function to find modulo inverse of a
bignum modInverse(bignum a, bignum m);

// Returns (a * b) % mod
bignum moduloMultiplication(bignum a, bignum b, bignum mod);

#endif