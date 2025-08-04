#pragma once

#include "prng/mt19937.h"
#include "prng/pcg32.h"
#include "prng/xoshiro128plusplus.h"

typedef enum {
    PRNG_MT19937 = 0,
    PRNG_PCG32,
    PRNG_XOSHIRO128PLUSPLUS
} prng_type;

#define PRNG_SEED(prng, s1, s2)                             \
    _Generic(prng,                                          \
        mt19937_t*:              mt19937_seed,              \
        pcg32_t*:                pcg32_seed,                \
        xoshiro128plusplus_t*:   xoshiro128plusplus_seed    \
    )(prng, s1, s2)

#define PRNG_RAND(prng)                                     \
    _Generic(prng,                                          \
        mt19937_t*:              mt19937_rand,              \
        pcg32_t*:                pcg32_rand,                \
        xoshiro128plusplus_t*:   xoshiro128plusplus_rand    \
    )(prng)
