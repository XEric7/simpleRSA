#include "tool.h"

bignum rsaEncrypt(bignum m, bignum e, bignum n)
{
    return powMod(m, e, n);
}

bignum rsaSign(bignum m, bignum d, bignum n)
{
    return powMod(m, d, n);
}