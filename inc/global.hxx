#pragma once

#include <cassert>

#ifdef DEBUG
  #define ASSERT(condition) assert(condition)
#else
  #define ASSERT(condition)
#endif
