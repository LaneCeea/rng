#pragma once
#include <stdint.h>

typedef struct {
    uint64_t state;
    uint64_t inc;
} pcg32_random_t;

void pcg32_seed(void* rng_v, uint64_t x, uint64_t y);
uint32_t pcg32_rand(void* rng_v);
