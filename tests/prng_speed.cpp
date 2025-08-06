#include "prng/wrapper.hpp"
#include "timer.hpp"

#include <random>
#include <cstdio>

template <PRNG Prng_t>
uint32_t Local(uint64_t s1, uint64_t s2, uint32_t iteration) {
    Prng_t Prng;
    Prng.seed(s1, s2);

    uint32_t x = 0;
    for (uint32_t i = 0; i < iteration; ++i) {
        x = Prng.rand();
    }
    {
        CPUTimer Timer(Prng.Name);
        for (uint32_t i = 0; i < iteration; ++i) {
            x = Prng.rand();
        }
    }
    return x;
}

int main() {
    std::random_device Device;
    uint64_t s1 = Device();
    uint64_t s2 = Device();
    uint32_t iteration = 1'000'000;

    std::printf("PRNG SPEED TESTING with %u iterations\n", iteration);
    std::printf("------------------------------------------------------------\n");
    
    Local<Pcg32<PrngTag::Global>>(s1, s2, iteration);
    Local<Standard<PrngTag::Global>>(s1, s2, iteration);
    Local<Xoshiro128plusplus<PrngTag::Global>>(s1, s2, iteration);
    Local<Mt19937<PrngTag::Global>>(s1, s2, iteration);
    
    Local<Pcg32<PrngTag::Local>>(s1, s2, iteration);
    Local<Xoshiro128plusplus<PrngTag::Local>>(s1, s2, iteration);
    Local<Mt19937<PrngTag::Local>>(s1, s2, iteration);

    std::printf("------------------------------------------------------------\n");
}