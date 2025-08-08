/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include "mt19937.h"

/* Period parameters */  
#define N MT19937_N
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static
void _init_genrand(mt19937_t* prng, unsigned long s) {
    prng->mt[0]= s & 0xffffffffUL;
    for (prng->mti=1; prng->mti<N; prng->mti++) {
        prng->mt[prng->mti] = 
	    (1812433253UL * (prng->mt[prng->mti-1] ^ (prng->mt[prng->mti-1] >> 30)) + prng->mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        prng->mt[prng->mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

static
void _init_by_array(mt19937_t* prng, unsigned long init_key[], int key_length) {
    int i, j, k;
    _init_genrand(prng, 19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        prng->mt[i] = (prng->mt[i] ^ ((prng->mt[i-1] ^ (prng->mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        prng->mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { prng->mt[0] = prng->mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        prng->mt[i] = (prng->mt[i] ^ ((prng->mt[i-1] ^ (prng->mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        prng->mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { prng->mt[0] = prng->mt[N-1]; i=1; }
    }

    prng->mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

void mt19937_seed(mt19937_t* prng, uint64_t s1, uint64_t s2) {
    unsigned long init_key[2] = { s1, s2 };
    _init_by_array(prng, init_key, 2);
}

uint32_t mt19937_rand(mt19937_t* prng) {
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (prng->mti >= N) { /* generate N words at one time */
        int kk;

        for (kk=0;kk<N-M;kk++) {
            y = (prng->mt[kk]&UPPER_MASK)|(prng->mt[kk+1]&LOWER_MASK);
            prng->mt[kk] = prng->mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (prng->mt[kk]&UPPER_MASK)|(prng->mt[kk+1]&LOWER_MASK);
            prng->mt[kk] = prng->mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (prng->mt[N-1]&UPPER_MASK)|(prng->mt[0]&LOWER_MASK);
        prng->mt[N-1] = prng->mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        prng->mti = 0;
    }
  
    y = prng->mt[prng->mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return (uint32_t)y;
}

static mt19937_t s_prng = { { 0U }, 0 };

void mt19937_seed_g(uint64_t s1, uint64_t s2) {
    mt19937_seed(&s_prng, s1, s2);
}

uint32_t mt19937_rand_g(void) {
    return mt19937_rand(&s_prng);
}
