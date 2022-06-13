#ifndef _rsa_h_
#define _rsa_h_

#include "tool.h"
bignum rsaEncrypt(bignum m, bignum e, bignum n);

bignum rsaSign(bignum m, bignum d, bignum n);

#endif