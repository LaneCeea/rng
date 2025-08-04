#include "timer.h"
#include "prng/interface.h"

#include <stdio.h>
#include <time.h>

void local_test(prng_type prng_t) {
    uint64_t s1 = time(NULL);
    uint64_t s2 = time(NULL);
    int n = 65536;
    uint32_t arr[n];
    TIMER_INIT(prng_timer);

    if (prng_t == PRNG_MT19937) {
        mt19937_t prng;
        PRNG_SEED(&prng, s1, s2);

        TIMER_START(prng_timer);
        for (int i = 0; i < n; ++i) {
            arr[i] = PRNG_RAND(&prng);
        }
        TIMER_STOP(prng_timer);

    } else if (prng_t == PRNG_PCG32) {
        pcg32_t prng;
        PRNG_SEED(&prng, s1, s2);

        TIMER_START(prng_timer);
        for (int i = 0; i < n; ++i) {
            arr[i] = PRNG_RAND(&prng);
        }
        TIMER_STOP(prng_timer);

    } else if (prng_t == PRNG_XOSHIRO128PLUSPLUS) {
        xoshiro128plusplus_t prng;
        PRNG_SEED(&prng, s1, s2);

        TIMER_START(prng_timer);
        for (int i = 0; i < n; ++i) {
            arr[i] = PRNG_RAND(&prng);
        }
        TIMER_STOP(prng_timer);

    }
    double millis = TIMER_ELAPSED_MSEC(prng_timer);
    printf("Elapsed: %.6f ms\n", millis);
}

void global_test(prng_type prng_t) {
    uint64_t s1 = time(NULL);
    uint64_t s2 = time(NULL);
    int n = 65536;
    uint32_t arr[n];
    TIMER_INIT(prng_timer);

    if (prng_t == PRNG_MT19937) {
        mt19937_seed_s(s1, s2);

        TIMER_START(prng_timer);
        for (int i = 0; i < n; ++i) {
            arr[i] = mt19937_rand_s();
        }
        TIMER_STOP(prng_timer);

    } else if (prng_t == PRNG_PCG32) {
        pcg32_seed_s(s1, s2);

        TIMER_START(prng_timer);
        for (int i = 0; i < n; ++i) {
            arr[i] = pcg32_rand_s();
        }
        TIMER_STOP(prng_timer);

    } else if (prng_t == PRNG_XOSHIRO128PLUSPLUS) {
        xoshiro128plusplus_seed_s(s1, s2);

        TIMER_START(prng_timer);
        for (int i = 0; i < n; ++i) {
            arr[i] = xoshiro128plusplus_rand_s();
        }
        TIMER_STOP(prng_timer);

    }
    double millis = TIMER_ELAPSED_MSEC(prng_timer);
    printf("Elapsed: %.6f ms\n", millis);
}

int main() {
    global_test(PRNG_MT19937);
    global_test(PRNG_PCG32);
    global_test(PRNG_XOSHIRO128PLUSPLUS);
    
    local_test(PRNG_MT19937);
    local_test(PRNG_PCG32);
    local_test(PRNG_XOSHIRO128PLUSPLUS);

    return 0;
}