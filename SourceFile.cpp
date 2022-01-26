  #include <iomanip>
  #include <iostream>
  #include <cstdint>
  #include <algorithm>
  #include <cmath>

  #include "clad/Differentiator/Differentiator.h"

  static inline float minD(float x, float y) { return x < y ? x : y; }
  static inline float maxD(float x, float y) { return x < y ? y : x; }
  static inline float clampD(float x, float a_min, float a_max) { return minD(a_max, maxD(x, a_min)); }

  static inline float GGX_Distribution(float cosThetaNH, float alpha)
  {
    const float alpha2  = alpha * alpha;
    const float NH_sqr  = clampD(cosThetaNH * cosThetaNH, 0.0f, 1.0f);
    const float den     = NH_sqr * alpha2 + (1.0f - NH_sqr);
    return alpha2 / std::max(M_PI * den * den, 1e-6f);             // maxD, std::max
  }

  int main(int argc, const char** argv)
  {
    auto mygrad = clad::gradient(GGX_Distribution);

    return 0;
  }
