#pragma once
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STANDARD_MIN 0
#define STANDARD_MAX RAND_MAX

void standard_seed_g(uint64_t s1, uint64_t s2);
uint32_t standard_rand_g();

#ifdef __cplusplus
}
#endif
