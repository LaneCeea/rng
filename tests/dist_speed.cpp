#include "prng.hpp"
#include "dist.hpp"
#include "timer.hpp"

#include <random>
#include <cstdio>
#include <sstream>

template <PRNG PrngT, DIST DistT>
float Test(uint64_t s1, uint64_t s2, typename DistT::ParamT Param, uint32_t iteration) {
    PrngT Prng(s1, s2);
    DistT Dist(Param);

    std::ostringstream Message;
    Message << Dist;

    float x = 0;
    for (uint32_t i = 0; i < iteration; ++i) {
        x = Dist(Prng);
    }
    {
        CPUTimer Timer(Message.str());
        for (uint32_t i = 0; i < iteration; ++i) {
            x = Dist(Prng);
        }
    }
    return x;
}

int main() {
    std::random_device Device;
    uint64_t s1 = Device();
    uint64_t s2 = Device();
    uint32_t iteration = 1'000'000;

    std::printf("DIST SPEED TESTING with %u iterations\n", iteration);
    std::printf("------------------------------------------------------------\n");
    
    Test<Pcg32<PrngTag::Local>, ContinuousUniform>(s1, s2, { 0.0, 1.0 }, iteration);
    Test<Pcg32<PrngTag::Local>, Normal>(s1, s2, { 0.0, 1.0 }, iteration);
    Test<Pcg32<PrngTag::Local>, Exponential>(s1, s2, { 1.0 }, iteration);

    std::printf("------------------------------------------------------------\n");
}