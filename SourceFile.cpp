#include "LiteMath.h"
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cmath>

#include "clad/Differentiator/Differentiator.h"

using LiteMath::M_PI;
using LiteMath::float3;

float ProjectX(float B[16], float V[4])
{
  float W = V[0] * B[3] + V[1] * B[7] + V[2] * B[11] + V[3] * B[15]; 
  return V[0]/W;
}

float NdcToScreenSpace(float x, float width)
{
  return (x*0.5f + 0.5f)*width - 0.5f;
}

float VS_X(float V[4], float B[16], float width)
{
  const float xNDC = ProjectX(B,V);
  return NdcToScreenSpace(xNDC, width);
}

//float VS_X(float V[4], float projM[16], float width)
//{
//  const float W    = V[0] * projM[3] + V[1] * projM[7] + V[2] * projM[11] + V[3]*projM[15]; 
//  const float xNDC = V[0]/W;
//  return (xNDC*0.5f + 0.5f)*width - 0.5f;
//}

struct Uniforms
{
  float projM[16];
  float width;
  float height;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
 
  Uniforms data = {
                    {1.0f, 0.3f, 0.2f, 0.1f,
                     0.3f, 1.0f, 0.1f, 0.1f,
                     0.2f, 0.2f, 1.0f, 0.1f,
                     0.1f, 0.1f, 0.1f, 1.0f},
                     1024.0f};

  std::cout << "HERE(1)" << std::endl;

  auto vsx_grad = clad::gradient(VS_X);

  std::cout << "HERE(2)" << std::endl;

  float vertex[4]       = {1,1,1,1};
  float result1[4+16+1] = {};
  
  vsx_grad.execute(vertex, data.projM, data.width,
                   clad::array_ref<float>(&result1[0], 4), clad::array_ref<float>(&result1[4], 16), clad::array_ref<float>(&result1[20], 1));

  std::cout << "HERE(3)" << std::endl;

  for(int i=0;i<21;i++)
    std::cout << i << ":\t" << result1[i] << std::endl;
 
  return 0;
}
