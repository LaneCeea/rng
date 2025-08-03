#include "prng/mt19937.h"
#include "prng/pcg32.h"
#include "prng/xoshiro128plusplus.h"
#include "prng/interface.h"

#include <stdio.h>

void rng_test(void* rng, seed_func seed, rand_func rand) {
    uint64_t x = 666U;
    uint64_t y = 888U;

    seed(rng, x, y);

    for (int i = 0; i < 10; ++i) {
        printf("%u\n", rand(rng));
    }
}

int main() {
    pcg32_random_t pcg32;
    rng_test(&pcg32, pcg32_seed, pcg32_rand);

    xoshiro128plusplus_random_t xoshiro128plusplus;
    rng_test(&xoshiro128plusplus, xoshiro128plusplus_seed, xoshiro128plusplus_rand);

    mt19937_random_t mt19937;
    rng_test(&mt19937, mt19937_seed, mt19937_rand);
    return 0;
}