#include "standard.h"

#include <stdlib.h>

void standard_seed_g(uint64_t s1, uint64_t s2) {
    unsigned int s = (unsigned int)((s1 ^ s2) ^ (s1 >> 32) ^ (s2 >> 32));
    srand(s);
}

uint32_t standard_rand_g(void) {
    return rand();
}
