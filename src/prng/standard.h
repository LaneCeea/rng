#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void standard_seed_g(uint64_t s1, uint64_t s2);
uint32_t standard_rand_g();

#ifdef __cplusplus
}
#endif
