#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XOSHIRO128PLUSPLUS_MIN 0
#define XOSHIRO128PLUSPLUS_MAX UINT32_MAX

typedef struct {
    uint32_t s[4];
} xoshiro128plusplus_t;

void xoshiro128plusplus_seed(xoshiro128plusplus_t* prng, uint64_t s1, uint64_t s2);
uint32_t xoshiro128plusplus_rand(xoshiro128plusplus_t* prng);

void xoshiro128plusplus_seed_g(uint64_t s1, uint64_t s2);
uint32_t xoshiro128plusplus_rand_g();

#ifdef __cplusplus
}
#endif
