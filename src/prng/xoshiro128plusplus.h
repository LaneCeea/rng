#pragma once
#include <stdint.h>

typedef struct {
    uint32_t s[4];
} xoshiro128plusplus_random_t;

void xoshiro128plusplus_seed(void* rng_v, uint64_t x, uint64_t y);
uint32_t xoshiro128plusplus_rand(void* rng_v);
