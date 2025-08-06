/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *       http://www.pcg-random.org
 */

#include "pcg32.h"

void pcg32_seed(pcg32_t* prng, uint64_t s1, uint64_t s2) {
    prng->state = 0U;
    prng->inc = (s2 << 1u) | 1u;
    pcg32_rand(prng);
    prng->state += s1;
    pcg32_rand(prng);
}

uint32_t pcg32_rand(pcg32_t* prng) {
    uint64_t oldstate = prng->state;
    prng->state = oldstate * 6364136223846793005ULL + prng->inc;
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

static pcg32_t s_prng;

void pcg32_seed_g(uint64_t s1, uint64_t s2) {
    pcg32_seed(&s_prng, s1, s2);
}

uint32_t pcg32_rand_g() {
    return pcg32_rand(&s_prng);
}