#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PCG32_MIN 0U
#define PCG32_MAX UINT32_MAX

typedef struct {
    uint64_t state;
    uint64_t inc;
} pcg32_t;

void pcg32_seed(pcg32_t* prng, uint64_t s1, uint64_t s2);
uint32_t pcg32_rand(pcg32_t* prng);

void pcg32_seed_g(uint64_t s1, uint64_t s2);
uint32_t pcg32_rand_g(void);

#ifdef __cplusplus
}
#endif
