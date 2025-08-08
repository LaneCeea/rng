#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CHATGPT_MIN 0U
#define CHATGPT_MAX UINT32_MAX

typedef struct {
    uint64_t state;
    uint64_t inc;
} chatgpt_t;

void chatgpt_seed(chatgpt_t* prng, uint64_t s1, uint64_t s2);
uint32_t chatgpt_rand(chatgpt_t* prng);

void chatgpt_seed_g(uint64_t s1, uint64_t s2);
uint32_t chatgpt_rand_g(void);

#ifdef __cplusplus
}
#endif
