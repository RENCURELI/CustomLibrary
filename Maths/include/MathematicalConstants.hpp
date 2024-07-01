#pragma once

// Variable Templates
template<floating_point FloatingPoint>
inline constexpr FloatingPoint e_v = static_cast<FloatingPoint>(2.718281828459045);

template<floating_point FloatingPoint>
inline constexpr FloatingPoint log2e_v = static_cast<FloatingPoint>(1.44269504088896340736);

template<floating_point FloatingPoint>
inline constexpr FloatingPoint log10e_v = static_cast<FloatingPoint>(0.434294481903251827651);

// Constants
inline constexpr double e = e_v<double>;
inline constexpr double log2e = log2e_v<double>;
inline constexpr double log10e = log10e_v<double>;