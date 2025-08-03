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

void xoshiro128plusplus_seed(void* rng_v, uint64_t x, uint64_t y) {
	xoshiro128plusplus_random_t* rng = rng_v;
    const uint64_t t1 = _splitmix64(x);
    const uint64_t t2 = _splitmix64(y);
    
    rng->s[0] = (uint32_t)t1;
    rng->s[1] = (uint32_t)(t1 >> 32);
    rng->s[2] = (uint32_t)t2;
    rng->s[3] = (uint32_t)(t2 >> 32);
}

uint32_t xoshiro128plusplus_rand(void* rng_v) {
	xoshiro128plusplus_random_t* rng = rng_v;
	const uint32_t result = _rotl(rng->s[0] + rng->s[3], 7) + rng->s[0];

	const uint32_t t = rng->s[1] << 9;

	rng->s[2] ^= rng->s[0];
	rng->s[3] ^= rng->s[1];
	rng->s[1] ^= rng->s[2];
	rng->s[0] ^= rng->s[3];

	rng->s[2] ^= t;

	rng->s[3] = _rotl(rng->s[3], 11);

	return result;
}
