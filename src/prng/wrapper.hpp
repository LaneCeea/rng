#pragma once

#include <concepts>
#include <string_view>
#include <cstdint>

#include "mt19937.h"
#include "pcg32.h"
#include "standard.h"
#include "xoshiro128plusplus.h"

template <class T>
concept PRNG = requires(T Prng, uint32_t s1, uint32_t s2) {
    Prng.seed(s1, s2);
    { Prng.rand() } -> std::same_as<uint32_t>;
    Prng.Name;
};

enum class PrngTag {
    Local = 0,
    Global
};

template <PrngTag T = PrngTag::Local>
class Mt19937;

template <PrngTag T = PrngTag::Local>
class Pcg32;

template <PrngTag T = PrngTag::Global>
    requires(T == PrngTag::Global)
class Standard;

template <PrngTag T = PrngTag::Local>
class Xoshiro128plusplus;

template<>
class Mt19937<PrngTag::Local> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        mt19937_seed(&m_Data, s1, s2);
    }

    uint32_t rand() {
        return mt19937_rand(&m_Data);
    }

public:
    static constexpr std::string_view Name = "Mt19937_Local";

private:
    mt19937_t m_Data;
};

template<>
class Mt19937<PrngTag::Global> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        mt19937_seed_g(s1, s2);
    }

    uint32_t rand() {
        return mt19937_rand_g();
    }

public:
    static constexpr std::string_view Name = "Mt19937_Global";
};

template<>
class Pcg32<PrngTag::Local> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        pcg32_seed(&m_Data, s1, s2);
    }

    uint32_t rand() {
        return pcg32_rand(&m_Data);
    }

public:
    static constexpr std::string_view Name = "Pcg32_Local";

private:
    pcg32_t m_Data;
};

template<>
class Pcg32<PrngTag::Global> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        pcg32_seed_g(s1, s2);
    }

    uint32_t rand() {
        return pcg32_rand_g();
    }

public:
    static constexpr std::string_view Name = "Pcg32_Global";
};

template<>
class Standard<PrngTag::Global> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        standard_seed_g(s1, s2);
    }

    uint32_t rand() {
        return standard_rand_g();
    }

public:
    static constexpr std::string_view Name = "Standard_Global";
};

template<>
class Xoshiro128plusplus<PrngTag::Local> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        xoshiro128plusplus_seed(&m_Data, s1, s2);
    }

    uint32_t rand() {
        return xoshiro128plusplus_rand(&m_Data);
    }

public:
    static constexpr std::string_view Name = "Xoshiro128plusplus_Local";

private:
    xoshiro128plusplus_t m_Data;
};

template<>
class Xoshiro128plusplus<PrngTag::Global> {
public:
    void seed(uint32_t s1, uint32_t s2) {
        xoshiro128plusplus_seed_g(s1, s2);
    }

    uint32_t rand() {
        return xoshiro128plusplus_rand_g();
    }

public:
    static constexpr std::string_view Name = "Xoshiro128plusplus_Global";
};
