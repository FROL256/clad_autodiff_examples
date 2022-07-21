#include "LiteMath.h"
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cmath>

#include "clad/Differentiator/Differentiator.h"

using LiteMath::M_PI;
using LiteMath::float3;


/*
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

float EvalGGX(float l[3], float v[3], float n[3], float roughness)
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
*/

struct CamInfo
{
  float projM[16];
  float width;
  float height;
};

void h(float a, float b, float output[]) {
    output[0] = a * a * a;
    output[1] = a * a * a + b * b * b;
    output[2] = 2 * (a + b);
}

//void h(float a[3], float b, float output[]) {
//    output[0] = a[3] * a[0] * a[0];
//    output[1] = a[0] * a[0] * a[0] + b * b * b;
//    output[2] = 2 * (a[0] + b);
//}

//void VertexShader(const float projM[16], const float width, const float height, float V[3], float output[2])
//{
//  const float W    =   V[0] * projM[3] + V[1] * projM[7] + V[2] * projM[11] + projM[15]; 
//  const float xNDC =  (V[0] * projM[0] + V[1] * projM[4] + V[2] * projM[ 8] + projM[12])/W;
//  const float yNDC = -(V[0] * projM[1] + V[1] * projM[5] + V[2] * projM[ 9] + projM[13])/W;
//  
//  output[0] = (xNDC*0.5f + 0.5f)*width;
//  output[1] = (yNDC*0.5f + 0.5f)*height; 
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct IgnoreMe
{
  float c;
};

float testFunc(float x, float y, const IgnoreMe* data)
{
  return x*y+data->c;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
  //float x = 1.0f;
  //float y = 2.0f;
  ////float xy[2] = {x,y};  
  //auto f_grad1 = clad::gradient(testFunc);
  //float result1[3] = {};
  //
  //IgnoreMe data;
  //data.c = 3.0f;
  //
  ////f_grad1.execute(x, y, data, &result1[0],  &result1[1]);
  ////testFunc_grad(x,y,data, &result1[0],  &result1[1]);
  //std::cout << "dx: " << result1[0] << ' ' << "dy: " << result1[1] << std::endl;
  
  
  CamInfo data = {
                    {1.0f, 0.3f, 0.2f, 0.1f,
                     0.3f, 1.0f, 0.1f, 0.1f,
                     0.2f, 0.2f, 1.0f, 0.1f,
                     0.1f, 0.1f, 0.1f, 1.0f},
                     1024.0f};

  std::cout << "HERE(1)" << std::endl;

  //auto vsx_grad = clad::gradient(VS_Y);
  auto h_jac = clad::jacobian(h);

  std::cout << "HERE(2)" << std::endl;

  float vertex[3] = {1,1,1};
  float result1[3] = {};
  
  //vsx_grad.execute(data.projM, vertex, data.width,
  //                 clad::array_ref<float>(&result1[0], 16), clad::array_ref<float>(&result1[16], 4), clad::array_ref<float>(&result1[20], 1));

  //VS_X_grad(data.projM, vertex, data.viewportWidth,
  //          clad::array_ref<float>(&result1[0], 16), clad::array_ref<float>(&result1[16], 4), clad::array_ref<float>(&result1[20], 1));


 
  return 0;
}
