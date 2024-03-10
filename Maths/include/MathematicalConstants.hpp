#pragma once

// Variable Templates
template<floating_point FloatingPoint>
inline constexpr FloatingPoint e_v = static_cast<FloatingPoint>(2.718281828459045);

// Constants
inline constexpr double e = e_v<double>;