/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide.

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#include "xoshiro128plusplus.h"

static inline
uint32_t _rotl(const uint32_t x, int k) {
	return (x << k) | (x >> (32 - k));
}

static inline
uint64_t _splitmix64(uint64_t x) {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void xoshiro128plusplus_seed(xoshiro128plusplus_t* prng, uint64_t s1, uint64_t s2) {
    const uint64_t t1 = _splitmix64(s1);
    const uint64_t t2 = _splitmix64(s2);
    
    prng->s[0] = (uint32_t)t1;
    prng->s[1] = (uint32_t)(t1 >> 32);
    prng->s[2] = (uint32_t)t2;
    prng->s[3] = (uint32_t)(t2 >> 32);
}

uint32_t xoshiro128plusplus_rand(xoshiro128plusplus_t* prng) {
	const uint32_t result = _rotl(prng->s[0] + prng->s[3], 7) + prng->s[0];

	const uint32_t t = prng->s[1] << 9;

	prng->s[2] ^= prng->s[0];
	prng->s[3] ^= prng->s[1];
	prng->s[1] ^= prng->s[2];
	prng->s[0] ^= prng->s[3];

	prng->s[2] ^= t;

	prng->s[3] = _rotl(prng->s[3], 11);

	return result;
}

static xoshiro128plusplus_t s_prng;

void xoshiro128plusplus_seed_g(uint64_t s1, uint64_t s2) {
    xoshiro128plusplus_seed(&s_prng, s1, s2);
}

uint32_t xoshiro128plusplus_rand_g() {
    return xoshiro128plusplus_rand(&s_prng);
}