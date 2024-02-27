#pragma once

#include <cassert>

#ifdef DEBUG
  #define ASSERT(condition) assert(condition)
#else
  #define ASSERT(condition)
#endif

constexpr double DEFAULT_LEARNING_RATE = 0.01;
constexpr double DEFAULT_EPSILON = 1e-8;
constexpr double DEFAULT_BETA1 = 0.9;
constexpr double DEFAULT_BETA2 = 0.999;
