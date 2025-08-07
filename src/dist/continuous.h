#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t x;
    uint32_t min;
    uint32_t max;
} prng_result_t;

float continuous_uniform1(prng_result_t rand);
float continuous_uniform(prng_result_t rand, float range_min, float range_max);

float standard_normal(prng_result_t rand);
float normal(prng_result_t rand, float mean, float variance);

float exponential(prng_result_t rand, float lambda);

#ifdef __cplusplus
}
#endif
