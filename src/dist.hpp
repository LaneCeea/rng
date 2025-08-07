#pragma once

#include "dist/continuous.h"

#include <concepts>
#include <string_view>
#include <cstdint>

template <class DistT>
concept DIST = requires(DistT dist, typename DistT::ParamT param, uint32_t prng_rand, uint32_t prng_min, uint32_t prng_max) {
    typename DistT::ResultT;
    typename DistT::ParamT;
    DistT{ param };
    { dist(prng_rand, prng_min, prng_max) } -> std::same_as<typename DistT::ResultT>;
    { dist.GetParam() } -> std::same_as<const typename DistT::ParamT&>;
    dist.SetParam(param);
    { DistT::Name } -> std::same_as<const std::string_view&>;
};

class ContinuousUniform {
public:
    using ResultT = float;
    struct ParamT {
        float min, max;

        constexpr ParamT() = default;
        constexpr ParamT(float a, float b) : min(a), max(b) {}
    };

public:
    ContinuousUniform() = default;
    ContinuousUniform(const ParamT& Param) : m_Param(Param) {}

    template <PRNG PrngT>
    ResultT operator()(PrngT& Prng) {
        return this->operator()(Prng.Rand(), Prng.Min, Prng.Max);
    }

    ResultT operator()(uint32_t prng_rand, uint32_t prng_min, uint32_t prng_max) {
        return continuous_uniform({ prng_rand, prng_min, prng_max }, m_Param.min, m_Param.max);
    }
    
    const ParamT& GetParam() const { return m_Param; }
    void SetParam(const ParamT& Param) { m_Param = Param; }

public:
    static constexpr std::string_view Name = "Continuous_Uniform";

private:
    ParamT m_Param;
};

class Normal {
public:
    using ResultT = float;
    struct ParamT {
        float mean, variance;

        constexpr ParamT() = default;
        constexpr ParamT(float m, float v) : mean(m), variance(v) {}
    };

public:
    Normal() = default;
    Normal(const ParamT& Param) : m_Param(Param) {}

    template <PRNG PrngT>
    ResultT operator()(PrngT& Prng) {
        return this->operator()(Prng.Rand(), Prng.Min, Prng.Max);
    }

    ResultT operator()(uint32_t prng_rand, uint32_t prng_min, uint32_t prng_max) {
        return normal({ prng_rand, prng_min, prng_max }, m_Param.mean, m_Param.variance);
    }
    
    const ParamT& GetParam() const { return m_Param; }
    void SetParam(const ParamT& Param) { m_Param = Param; }

public:
    static constexpr std::string_view Name = "Normal";

private:
    ParamT m_Param;
};

class Exponential {
public:
    using ResultT = float;
    struct ParamT {
        float lambda;

        constexpr ParamT() = default;
        constexpr ParamT(float a) : lambda(a) {}
    };

public:
    Exponential() = default;
    Exponential(const ParamT& Param) : m_Param(Param) {}

    template <PRNG PrngT>
    ResultT operator()(PrngT& Prng) {
        return this->operator()(Prng.Rand(), Prng.Min, Prng.Max);
    }

    ResultT operator()(uint32_t prng_rand, uint32_t prng_min, uint32_t prng_max) {
        return exponential({ prng_rand, prng_min, prng_max }, m_Param.lambda);
    }
    
    const ParamT& GetParam() const { return m_Param; }
    void SetParam(const ParamT& Param) { m_Param = Param; }

public:
    static constexpr std::string_view Name = "Exponential";

private:
    ParamT m_Param;
};
