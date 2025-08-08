#pragma once

#include <concepts>
#include <string_view>
#include <cstdint>

#include "prng/chatgpt.h"
#include "prng/mt19937.h"
#include "prng/pcg32.h"
#include "prng/standard.h"
#include "prng/xoshiro128plusplus.h"

template <class PrngT>
concept PRNG = requires(PrngT prng, uint32_t s1, uint32_t s2) {
    PrngT{ s1, s2 };
    prng.Seed(s1, s2);
    { prng.Rand() } -> std::same_as<uint32_t>;
    { PrngT::Min } -> std::same_as<const uint32_t&>;
    { PrngT::Max } -> std::same_as<const uint32_t&>;
    { PrngT::Name } -> std::same_as<const std::string_view&>;
};

enum class PrngTag {
    Local = 0,
    Global
};

template <PrngTag T = PrngTag::Local>
class Chatgpt;

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
class Chatgpt<PrngTag::Local> {
public:
    Chatgpt(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        chatgpt_seed(&m_Data, s1, s2);
    }

    uint32_t Rand() {
        return chatgpt_rand(&m_Data);
    }

public:
    static constexpr uint32_t Min = CHATGPT_MIN;
    static constexpr uint32_t Max = CHATGPT_MAX;
    static constexpr std::string_view Name = "Chatgpt_Local";

private:
    chatgpt_t m_Data;
};

template<>
class Chatgpt<PrngTag::Global> {
public:
    Chatgpt(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        chatgpt_seed_g(s1, s2);
    }

    uint32_t Rand() {
        return chatgpt_rand_g();
    }

public:
    static constexpr uint32_t Min = CHATGPT_MIN;
    static constexpr uint32_t Max = CHATGPT_MAX;
    static constexpr std::string_view Name = "Chatgpt_Global";
};

template<>
class Mt19937<PrngTag::Local> {
public:
    Mt19937(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        mt19937_seed(&m_Data, s1, s2);
    }

    uint32_t Rand() {
        return mt19937_rand(&m_Data);
    }

public:
    static constexpr uint32_t Min = MT19937_MIN;
    static constexpr uint32_t Max = MT19937_MAX;
    static constexpr std::string_view Name = "Mt19937_Local";

private:
    mt19937_t m_Data;
};

template<>
class Mt19937<PrngTag::Global> {
public:
    Mt19937(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        mt19937_seed_g(s1, s2);
    }

    uint32_t Rand() {
        return mt19937_rand_g();
    }

public:
    static constexpr uint32_t Min = MT19937_MIN;
    static constexpr uint32_t Max = MT19937_MAX;
    static constexpr std::string_view Name = "Mt19937_Global";
};

template<>
class Pcg32<PrngTag::Local> {
public:
    Pcg32(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        pcg32_seed(&m_Data, s1, s2);
    }

    uint32_t Rand() {
        return pcg32_rand(&m_Data);
    }

public:
    static constexpr uint32_t Min = PCG32_MIN;
    static constexpr uint32_t Max = PCG32_MAX;
    static constexpr std::string_view Name = "Pcg32_Local";

private:
    pcg32_t m_Data;
};

template<>
class Pcg32<PrngTag::Global> {
public:
    Pcg32(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        pcg32_seed_g(s1, s2);
    }

    uint32_t Rand() {
        return pcg32_rand_g();
    }

public:
    static constexpr uint32_t Min = PCG32_MIN;
    static constexpr uint32_t Max = PCG32_MAX;
    static constexpr std::string_view Name = "Pcg32_Global";
};

template<>
class Standard<PrngTag::Global> {
public:
    Standard(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        standard_seed_g(s1, s2);
    }

    uint32_t Rand() {
        return standard_rand_g();
    }

public:
    static constexpr uint32_t Min = STANDARD_MIN;
    static constexpr uint32_t Max = STANDARD_MAX;
    static constexpr std::string_view Name = "Standard_Global";
};

template<>
class Xoshiro128plusplus<PrngTag::Local> {
public:
    Xoshiro128plusplus(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        xoshiro128plusplus_seed(&m_Data, s1, s2);
    }

    uint32_t Rand() {
        return xoshiro128plusplus_rand(&m_Data);
    }

public:
    static constexpr uint32_t Min = XOSHIRO128PLUSPLUS_MIN;
    static constexpr uint32_t Max = XOSHIRO128PLUSPLUS_MAX;
    static constexpr std::string_view Name = "Xoshiro128plusplus_Local";

private:
    xoshiro128plusplus_t m_Data;
};

template<>
class Xoshiro128plusplus<PrngTag::Global> {
public:
    Xoshiro128plusplus(uint32_t s1, uint32_t s2) {
        Seed(s1, s2);
    }

    void Seed(uint32_t s1, uint32_t s2) {
        xoshiro128plusplus_seed_g(s1, s2);
    }

    uint32_t Rand() {
        return xoshiro128plusplus_rand_g();
    }

public:
    static constexpr uint32_t Min = XOSHIRO128PLUSPLUS_MIN;
    static constexpr uint32_t Max = XOSHIRO128PLUSPLUS_MAX;
    static constexpr std::string_view Name = "Xoshiro128plusplus_Global";
};
