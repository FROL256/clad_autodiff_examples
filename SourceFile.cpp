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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float f(float arr[2]) { return arr[0] + arr[1]; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//static inline void mat4_colmajor_mul_vec4(float RES[4], const float B[16], const float V[4]) // modern gcc compiler succesfuly vectorize such implementation!
//{
//	RES[0] = V[0] * B[0] + V[1] * B[4] + V[2] * B[ 8] + V[3] * B[12];
//	RES[1] = V[0] * B[1] + V[1] * B[5] + V[2] * B[ 9] + V[3] * B[13];
//	RES[2] = V[0] * B[2] + V[1] * B[6] + V[2] * B[10] + V[3] * B[14];
//	RES[3] = V[0] * B[3] + V[1] * B[7] + V[2] * B[11] + V[3] * B[15];
//}

//static inline float4 swglClipSpaceToScreenSpaceTransform(float4 a_pos, const float4 viewportf) // pre (g_pContext != nullptr)
//{
//  const float fw = viewportf.z;
//  const float fh = viewportf.w;
//
//  const float x  = a_pos.x*0.5f + 0.5f;
//  const float y  = a_pos.y*0.5f + 0.5f;
//
//  return float4(x*fw - 0.5f + viewportf.x, y*fh - 0.5f + viewportf.y, a_pos.z, a_pos.w);
//}

struct CamInfo
{
  float projM[16];
  float width;
  float height;
};

static inline float VS_X(float V[3], const CamInfo& data)
{
  const float W    =  V[0] * data.projM[3] + V[1] * data.projM[7] + V[2] * data.projM[11] + data.projM[15]; 
  const float xNDC = (V[0] * data.projM[0] + V[1] * data.projM[4] + V[2] * data.projM[ 8] + data.projM[12])/W;
  return (xNDC*0.5f + 0.5f)*data.width;
}

static inline float VS_Y(float V[3], const CamInfo& data)
{
  const float W    =   V[0] * data.projM[3] + V[1] * data.projM[7] + V[2] * data.projM[11] + data.projM[15]; 
  const float xNDC = -(V[0] * data.projM[1] + V[1] * data.projM[5] + V[2] * data.projM[ 9] + data.projM[13])/W;
  return (xNDC*0.5f + 0.5f)*data.height;
}

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

  auto vsx_grad = clad::gradient(VS_Y);

  std::cout << "HERE(2)" << std::endl;

  float vertex[3] = {1,1,1};
  float result1[3] = {};
  
  //vsx_grad.execute(data.projM, vertex, data.width,
  //                 clad::array_ref<float>(&result1[0], 16), clad::array_ref<float>(&result1[16], 4), clad::array_ref<float>(&result1[20], 1));

  //VS_X_grad(data.projM, vertex, data.viewportWidth,
  //          clad::array_ref<float>(&result1[0], 16), clad::array_ref<float>(&result1[16], 4), clad::array_ref<float>(&result1[20], 1));

  std::cout << "HERE(3)" << std::endl;

  for(int i=0;i<21;i++)
    std::cout << i << ":\t" << result1[i] << std::endl;
  

  /*
  auto ggx_grad = clad::gradient(EvalGGX);

  float3 lightDir = LiteMath::normalize(float3(-1,1,0));
  float3 viewDir  = LiteMath::normalize(float3(+1,1,0));
  float3 normal   = LiteMath::normalize(float3(0.25f,1,0));
  float roughness = 0.5f;

  float result1[10] = {};
  ggx_grad.execute(lightDir.M, viewDir.M, normal.M, roughness, 
                   &result1[0], &result1[3], &result1[6], &result1[9]);
  
  //EvalGGX_grad(lightDir.M, viewDir.M, normal.M, roughness, 
  //             &result1[0], &result1[3], &result1[6], &result1[9]);

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
  */
 
  return 0;
}
