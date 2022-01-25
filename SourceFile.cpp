#include "LiteMath.h"
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cmath>

#include "clad/Differentiator/Differentiator.h"

using LiteMath::M_PI;
using LiteMath::float3;


static inline float minD(float x, float y) { return x < y ? x : y; }
static inline float maxD(float x, float y) { return x < y ? y : x; }
static inline float clampD(float x, float a_min, float a_max) { return minD(a_max, maxD(x, a_min)); }


static inline float GGX_Distribution(float cosThetaNH, float alpha)
{
  const float alpha2  = alpha * alpha;
  const float NH_sqr  = clampD(cosThetaNH * cosThetaNH, 0.0f, 1.0f);
  const float den     = NH_sqr * alpha2 + (1.0f - NH_sqr);
  return alpha2 / maxD(M_PI * den * den, 1e-6f);
}

static inline float GGX_GeomShadMask(const float cosThetaN, const float alpha)
{
  const float cosTheta_sqr = clampD(cosThetaN*cosThetaN, 0.0f, 1.0f);
  const float tan2         = (1.0f - cosTheta_sqr) / maxD(cosTheta_sqr, 1e-6f);
  const float GP           = 2.0f / (1.0f + std::sqrt(1.0f + alpha * alpha * tan2));
  return GP;
}

static inline float EvalGGX(float l[3], float v[3], float n[3], float roughness)
{
  float h[3]; // const float3 h = normalize(v + l); // half vector
  {
    h[0] = l[0] + v[0];
    h[1] = l[1] + v[1];
    h[2] = l[2] + v[2];
    const float lenInv = 1.0f/( std::sqrt(h[0]*h[0] + h[1]*h[1] + h[2]*h[2]) ); 
    h[0] *= lenInv;
    h[1] *= lenInv;
    h[2] *= lenInv;
  }

  const float dotNH = n[0]*h[0] + n[1]*h[1] + n[2]*h[2]; // dot(n, h);
  const float dotNV = n[0]*v[0] + n[1]*v[1] + n[2]*v[2]; // dot(n, v);
  const float dotNL = n[0]*l[0] + n[1]*l[1] + n[2]*l[2]; // dot(n, l);
  const float roughSqr = roughness * roughness;
  const float D = GGX_Distribution(dotNH, roughSqr);
  const float G = GGX_GeomShadMask(dotNV, roughSqr) * GGX_GeomShadMask(dotNL, roughSqr); 
  return (D * G)/maxD(4.0f * dotNV * dotNL, 1e-6f); 
} 

float f(float arr[2]) { return arr[0] + arr[1]; }


int main(int argc, const char** argv)
{
  //float x = 1.0f;
  //float y = 2.0f;
  //float xy[2] = {x,y};  
  //auto f_grad1 = clad::gradient(f);
  //float result1[2] = {};
  //f_grad1.execute(xy, &result1[0]);
  //std::cout << "dx: " << result1[0] << ' ' << "dy: " << result1[1] << std::endl;

  auto ggx_grad = clad::gradient(EvalGGX);

  float3 lightDir = LiteMath::normalize(float3(-1,1,0));
  float3 viewDir  = LiteMath::normalize(float3(+1,1,0));
  float3 normal   = LiteMath::normalize(float3(0.25f,1,0));
  float roughness = 0.5f;

  float result1[10] = {};
  ggx_grad.execute(lightDir.M, viewDir.M, normal.M, roughness, 
                   &result1[0], &result1[3], &result1[6], &result1[9]);
  

  // check with brute force approach
  // 
  const float dEpsilon = 1e-4f;
  const float ggxValue = EvalGGX(lightDir.M, viewDir.M, normal.M, roughness);
  float result2[10] = {};

  // 0,1,2 ==> viewDir
  {
    float3 lightDir1 = lightDir + float3(dEpsilon,0,0);
    float3 lightDir2 = lightDir + float3(0,dEpsilon,0);
    float3 lightDir3 = lightDir + float3(0,0,dEpsilon);
    result2[0] = (EvalGGX(lightDir1.M, viewDir.M, normal.M, roughness) - ggxValue)/dEpsilon;
    result2[1] = (EvalGGX(lightDir2.M, viewDir.M, normal.M, roughness) - ggxValue)/dEpsilon;
    result2[2] = (EvalGGX(lightDir3.M, viewDir.M, normal.M, roughness) - ggxValue)/dEpsilon;
  }

  // 3,4,5 ==> lightDir
  {
    float3 viewDir1 = viewDir + float3(dEpsilon,0,0);
    float3 viewDir2 = viewDir + float3(0,dEpsilon,0);
    float3 viewDir3 = viewDir + float3(0,0,dEpsilon);
    result2[3] = (EvalGGX(lightDir.M, viewDir1.M, normal.M, roughness) - ggxValue)/dEpsilon;
    result2[4] = (EvalGGX(lightDir.M, viewDir2.M, normal.M, roughness) - ggxValue)/dEpsilon;
    result2[5] = (EvalGGX(lightDir.M, viewDir3.M, normal.M, roughness) - ggxValue)/dEpsilon;
  }

  // 7,8,9 ==> normal
  {
    float3 normal1 = normal + float3(dEpsilon,0,0);
    float3 normal2 = normal + float3(0,dEpsilon,0);
    float3 normal3 = normal + float3(0,0,dEpsilon);
    result2[6] = (EvalGGX(lightDir.M, viewDir.M, normal1.M, roughness) - ggxValue)/dEpsilon;
    result2[7] = (EvalGGX(lightDir.M, viewDir.M, normal2.M, roughness) - ggxValue)/dEpsilon;
    result2[8] = (EvalGGX(lightDir.M, viewDir.M, normal3.M, roughness) - ggxValue)/dEpsilon;
  }

  result2[9] = (EvalGGX(lightDir.M, viewDir.M, normal.M, roughness+dEpsilon) - ggxValue)/dEpsilon;

  for(int i=0;i<10;i++)
    std::cout << std::setw(10) << std::right << result1[i] << " | " << result2[i] << std::endl;

  return 0;
}
