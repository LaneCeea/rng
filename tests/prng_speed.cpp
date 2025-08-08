#include "prng.hpp"
#include "timer.hpp"

#include <random>
#include <cstdio>

template <PRNG PrngT>
uint32_t Test(uint64_t s1, uint64_t s2, uint32_t iteration) {
    PrngT Prng(s1, s2);

    uint32_t x = 0;
    for (uint32_t i = 0; i < iteration; ++i) {
        x = Prng.Rand();
    }
    {
        CPUTimer Timer(std::string(Prng.Name));
        for (uint32_t i = 0; i < iteration; ++i) {
            x = Prng.Rand();
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
    
    Test<Pcg32<PrngTag::Global>>(s1, s2, iteration);
    Test<Standard<PrngTag::Global>>(s1, s2, iteration);
    Test<Xoshiro128plusplus<PrngTag::Global>>(s1, s2, iteration);
    Test<Mt19937<PrngTag::Global>>(s1, s2, iteration);
    Test<Chatgpt<PrngTag::Global>>(s1, s2, iteration);
    
    Test<Pcg32<PrngTag::Local>>(s1, s2, iteration);
    Test<Xoshiro128plusplus<PrngTag::Local>>(s1, s2, iteration);
    Test<Mt19937<PrngTag::Local>>(s1, s2, iteration);
    Test<Chatgpt<PrngTag::Local>>(s1, s2, iteration);

    std::printf("------------------------------------------------------------\n");
}