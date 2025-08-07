#include "prng.hpp"
#include "dist.hpp"
#include "config.h"
#include "timer.hpp"

#include <random>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>

template <PRNG PrngT, DIST DistT>
void Generate(uint64_t s1, uint64_t s2, typename DistT::ParamT Param, uint32_t count, std::filesystem::path OutputDir) {
    PrngT Prng(s1, s2);
    DistT Dist(Param);

    std::filesystem::path OutputFile = OutputDir / Dist.Name;
    OutputFile.replace_extension("txt");
    std::ofstream FileStream(OutputFile);
    FileStream << std::setprecision(6);
    std::ostringstream Message;
    Message << Dist;

    {
        CPUTimer Timer(Message.str());
        for (uint32_t i = 0; i < count; ++i) {
            FileStream << Dist(Prng) << '\n';
        }
    }
}

int main() {
    std::filesystem::path Root(PROJECT_ROOT);
    std::filesystem::path OutputDir = Root / "output";
    std::filesystem::create_directory(OutputDir);

    std::random_device Device;
    uint64_t s1 = Device();
    uint64_t s2 = Device();
    uint32_t count = 1'000;

    std::printf("DIST GEN generate %u output\n", count);
    std::printf("------------------------------------------------------------\n");
    
    Generate<Pcg32<PrngTag::Local>, ContinuousUniform>(s1, s2, { 0.0, 1.0 }, count, OutputDir);
    Generate<Pcg32<PrngTag::Local>, Normal>(s1, s2, { 0.0, 1.0 }, count, OutputDir);
    Generate<Pcg32<PrngTag::Local>, Exponential>(s1, s2, { 1.0 }, count, OutputDir);

    std::printf("------------------------------------------------------------\n");
}