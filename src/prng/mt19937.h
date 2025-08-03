#pragma once
#include <stdint.h>

#define MT19937_N 624

typedef struct {
    uint64_t mt[MT19937_N];
    int mti;
} mt19937_random_t;

void mt19937_seed(void* rng_v, uint64_t x, uint64_t y);
uint32_t mt19937_rand(void* rng_v);
