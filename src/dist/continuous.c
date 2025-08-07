#include "continuous.h"

#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// internal double-precision helper
////////////////////////////////////////////////////////////////////////////////

static inline
double _continuous_uniform1(prng_result_t rand);

static
double _inverse_standard_normal_cdf(double p);

static inline
double _standard_normal(prng_result_t rand);

static inline
double _inverse_exponential_cdf(double p, double lambda);

////////////////////////////////////////////////////////////////////////////////
// definition
////////////////////////////////////////////////////////////////////////////////

static inline
double _continuous_uniform1(prng_result_t rand) {
    return (double)rand.x / (double)(rand.max - rand.min);
}

float continuous_uniform1(prng_result_t rand) {
    return (float)_continuous_uniform1(rand);
}

float continuous_uniform(prng_result_t rand, float range_min, float range_max) {
    return (float)(_continuous_uniform1(rand) * (range_max - range_min) + range_min);
}

/*
 * Inverse standard normal cumulative distribution function
 * Implementation based on the Beasley-Springer-Moro algorithm
 * 
 * Reference:
 * Beasley, J. D., & Springer, S. G. (1977). 
 * Algorithm AS 111: The Percentage Points of the Normal Distribution. 
 * Journal of the Royal Statistical Society, Series C (Applied Statistics), 
 * 26(1), 118-121.
 *
 * This algorithm uses rational approximations in three regions:
 * - Lower tail: 0.0 < p < 0.02425
 * - Upper tail: 0.97575 < p < 1.0
 * - Central region: 0.02425 <= p <= 0.97575
 */
static
double _inverse_standard_normal_cdf(double p) {
    if (p < 0.0 || p > 1.0) {
        return NAN;
    } else if (p == 0.0) {
        return -HUGE_VAL;
    } else if (p == 1.0) {
        return HUGE_VAL;
    }

    // Coefficients in rational approximations
    const double a[6] = {
        -3.969683028665376e+01,
         2.209460984245205e+02,
        -2.759285104469687e+02,
         1.383577518672690e+02,
        -3.066479806614716e+01,
         2.506628277459239e+00
    };

    const double b[5] = {
        -5.447609879822406e+01,
         1.615858368580409e+02,
        -1.556989798598866e+02,
         6.680131188771972e+01,
        -1.328068155288572e+01
    };

    const double c[6] = {
        -7.784894002430293e-03,
        -3.223964580411365e-01,
        -2.400758277161838e+00,
        -2.549732539343734e+00,
         4.374664141464968e+00,
         2.938163982698783e+00
    };

    const double d[4] = {
         7.784695709041462e-03,
         3.224671290700398e-01,
         2.445134137142996e+00,
         3.754408661907416e+00
    };

    // Break-points
    const double plow  = 0.02425;
    const double phigh = 1 - plow;

    if (p < plow) {
        // Rational approximation for lower region
        double q = sqrt(-2 * log(p));
        return (((((
            c[0]*q + c[1])*q + c[2])*q + c[3])*q + c[4])*q + c[5]) /
               ((((d[0]*q + d[1])*q + d[2])*q + d[3])*q + 1);
    } else if (p > phigh) {
        // Rational approximation for upper region
        double q = sqrt(-2 * log(1 - p));
        return -((((( 
            c[0]*q + c[1])*q + c[2])*q + c[3])*q + c[4])*q + c[5]) /
                ((((d[0]*q + d[1])*q + d[2])*q + d[3])*q + 1);
    } else {
        // Rational approximation for central region
        double q = p - 0.5;
        double r = q * q;
        return (((((a[0]*r + a[1])*r + a[2])*r + a[3])*r + a[4])*r + a[5]) * q /
               (((((b[0]*r + b[1])*r + b[2])*r + b[3])*r + b[4])*r + 1);
    }
}

static inline
double _standard_normal(prng_result_t rand) {
    return _inverse_standard_normal_cdf(_continuous_uniform1(rand));
}

float standard_normal(prng_result_t rand) {
    return (float)_standard_normal(rand);
}

float normal(prng_result_t rand, float mean, float variance) {
    return _standard_normal(rand) * variance + mean;
}

static inline
double _inverse_exponential_cdf(double p, double lambda) {
    // y = 1 - exp(-lambda * x)
    // -lambda * x = ln(1 - y)
    // x = -1/lambda ln(1 - y)
    if (p == 1.0) {
        return HUGE_VAL;
    }
    return -log(1 - p) / lambda;
}

float exponential(prng_result_t rand, float lambda) {
    return _inverse_exponential_cdf(_continuous_uniform1(rand), lambda);
}
