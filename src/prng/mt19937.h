#pragma once
#include <stdint.h>

#define MT19937_N 624

typedef struct {
    uint64_t mt[MT19937_N];
    int mti;
} mt19937_t;

void mt19937_seed(mt19937_t* prng, uint64_t s1, uint64_t s2);
uint32_t mt19937_rand(mt19937_t* prng);

void mt19937_seed_s(uint64_t s1, uint64_t s2);
uint32_t mt19937_rand_s();
