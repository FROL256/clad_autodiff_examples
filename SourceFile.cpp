#include "LiteMath.h"
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include <chrono>

#include "clad/Differentiator/Differentiator.h"

using LiteMath::M_PI;
using LiteMath::float3;


struct CamInfo
{
  float projM[16];
  float width;
  float height;
};

//static inline float VS_X(float V[3], float projM[16], float width)
//{
//  const float W    =  V[0] * projM[3] + V[1] * projM[7] + V[2] * projM[11] + projM[15]; 
//  const float xNDC = (V[0] * projM[0] + V[1] * projM[4] + V[2] * projM[ 8] + projM[12])/W;
//  return (xNDC*0.5f + 0.5f)*width;
//}
//
//static inline float VS_Y(float V[3], float projM[16], float height)
//{
//  const float W    =   V[0] * projM[3] + V[1] * projM[7] + V[2] * projM[11] + projM[15]; 
//  const float xNDC = -(V[0] * projM[1] + V[1] * projM[5] + V[2] * projM[ 9] + projM[13])/W;
//  return (xNDC*0.5f + 0.5f)*height;
//}


static inline float ProjectX(float V[3], float projM[16])
{
  const float W    =  V[0] * projM[3] + V[1] * projM[7] + V[2] * projM[11] + projM[15]; 
  const float xNDC = (V[0] * projM[0] + V[1] * projM[4] + V[2] * projM[ 8] + projM[12])/W;
  return xNDC;
}

static inline float NdcToScreenSpace(float x, float width)
{
  return (x*0.5f + 0.5f)*width - 0.5f;
}

static inline float VS_X(float V[3], float projM[16], float width)
{
  const float xNDC = ProjectX(V, projM);
  return NdcToScreenSpace(xNDC, width);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline void VS_X_grad_v1(float V[3], float projM[16], float width, 
                   clad::array_ref<float> _d_V, clad::array_ref<float> _d_projM, clad::array_ref<float> _d_width) {
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    float _t4;
    float _t5;
    float _d_W = 0;
    float _t6;
    float _t7;
    float _t8;
    float _t9;
    float _t10;
    float _t11;
    float _t12;
    float _t13;
    float _d_xNDC = 0;
    float _t14;
    float _t15;
    _t1 = V[0];
    _t0 = projM[3];
    _t3 = V[1];
    _t2 = projM[7];
    _t5 = V[2];
    _t4 = projM[11];
    const float W = _t1 * _t0 + _t3 * _t2 + _t5 * _t4 + projM[15];
    _t8 = V[0];
    _t7 = projM[0];
    _t10 = V[1];
    _t9 = projM[4];
    _t12 = V[2];
    _t11 = projM[8];
    _t13 = (_t8 * _t7 + _t10 * _t9 + _t12 * _t11 + projM[12]);
    _t6 = W;
    const float xNDC = _t13 / _t6;
    _t15 = (xNDC * 0.5F + 0.5F);
    _t14 = width;
    float VS_X_return = _t15 * _t14;
    goto _label0;
  _label0:
    {
        float _r14 = 1 * _t14;
        float _r15 = _r14 * 0.5F;
        _d_xNDC += _r15;
        float _r16 = _t15 * 1;
        * _d_width += _r16;
    }
    {
        float _r6 = _d_xNDC / _t6;
        float _r7 = _r6 * _t7;
        _d_V[0] += _r7;
        float _r8 = _t8 * _r6;
        _d_projM[0] += _r8;
        float _r9 = _r6 * _t9;
        _d_V[1] += _r9;
        float _r10 = _t10 * _r6;
        _d_projM[4] += _r10;
        float _r11 = _r6 * _t11;
        _d_V[2] += _r11;
        float _r12 = _t12 * _r6;
        _d_projM[8] += _r12;
        _d_projM[12] += _r6;
        float _r13 = _d_xNDC * -_t13 / (_t6 * _t6);
        _d_W += _r13;
    }
    {
        float _r0 = _d_W * _t0;
        _d_V[0] += _r0;
        float _r1 = _t1 * _d_W;
        _d_projM[3] += _r1;
        float _r2 = _d_W * _t2;
        _d_V[1] += _r2;
        float _r3 = _t3 * _d_W;
        _d_projM[7] += _r3;
        float _r4 = _d_W * _t4;
        _d_V[2] += _r4;
        float _r5 = _t5 * _d_W;
        _d_projM[11] += _r5;
        _d_projM[15] += _d_W;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline void ProjectX_grad(float V[3], float projM[16], clad::array_ref<float> _d_V, clad::array_ref<float> _d_projM) {
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    float _t4;
    float _t5;
    float _d_W = 0;
    float _t6;
    float _t7;
    float _t8;
    float _t9;
    float _t10;
    float _t11;
    float _t12;
    float _t13;
    float _d_xNDC = 0;
    _t1 = V[0];
    _t0 = projM[3];
    _t3 = V[1];
    _t2 = projM[7];
    _t5 = V[2];
    _t4 = projM[11];
    const float W = _t1 * _t0 + _t3 * _t2 + _t5 * _t4 + projM[15];
    _t8 = V[0];
    _t7 = projM[0];
    _t10 = V[1];
    _t9 = projM[4];
    _t12 = V[2];
    _t11 = projM[8];
    _t13 = (_t8 * _t7 + _t10 * _t9 + _t12 * _t11 + projM[12]);
    _t6 = W;
    const float xNDC = _t13 / _t6;
    float ProjectX_return = xNDC;
    goto _label0;
  _label0:
    _d_xNDC += 1;
    {
        float _r6 = _d_xNDC / _t6;
        float _r7 = _r6 * _t7;
        _d_V[0] += _r7;
        float _r8 = _t8 * _r6;
        _d_projM[0] += _r8;
        float _r9 = _r6 * _t9;
        _d_V[1] += _r9;
        float _r10 = _t10 * _r6;
        _d_projM[4] += _r10;
        float _r11 = _r6 * _t11;
        _d_V[2] += _r11;
        float _r12 = _t12 * _r6;
        _d_projM[8] += _r12;
        _d_projM[12] += _r6;
        float _r13 = _d_xNDC * -_t13 / (_t6 * _t6);
        _d_W += _r13;
    }
    {
        float _r0 = _d_W * _t0;
        _d_V[0] += _r0;
        float _r1 = _t1 * _d_W;
        _d_projM[3] += _r1;
        float _r2 = _d_W * _t2;
        _d_V[1] += _r2;
        float _r3 = _t3 * _d_W;
        _d_projM[7] += _r3;
        float _r4 = _d_W * _t4;
        _d_V[2] += _r4;
        float _r5 = _t5 * _d_W;
        _d_projM[11] += _r5;
        _d_projM[15] += _d_W;
    }
}
static inline void NdcToScreenSpace_grad(float x, float width, clad::array_ref<float> _d_x, clad::array_ref<float> _d_width) {
    float _t0;
    float _t1;
    _t1 = (x * 0.5F + 0.5F);
    _t0 = width;
    float NdcToScreenSpace_return = _t1 * _t0 - 0.5F;
    goto _label0;
  _label0:
    {
        float _r0 = 1 * _t0;
        float _r1 = _r0 * 0.5F;
        * _d_x += _r1;
        float _r2 = _t1 * 1;
        * _d_width += _r2;
    }
}
static inline void VS_X_grad_v2(float V[3], float projM[16], float width, clad::array_ref<float> _d_V, clad::array_ref<float> _d_projM, clad::array_ref<float> _d_width) {
    float *_t0;
    float *_t1;
    float _d_xNDC = 0;
    float _t2;
    float _t3;
    _t0 = V;
    _t1 = projM;
    const float xNDC = ProjectX(_t0, _t1);
    _t2 = xNDC;
    _t3 = width;
    float VS_X_return = NdcToScreenSpace(_t2, _t3);
    goto _label0;
  _label0:
    {
        float _grad2 = 0.F;
        float _grad3 = 0.F;
        NdcToScreenSpace_grad(_t2, _t3, &_grad2, &_grad3);
        float _r2 = 1 * _grad2;
        _d_xNDC += _r2;
        float _r3 = 1 * _grad3;
        * _d_width += _r3;
    }
    {
        clad::array<float> _grad0(_d_V.size());
        clad::array<float> _grad1(_d_projM.size());
        ProjectX_grad(_t0, _t1, _grad0, _grad1);
        clad::array_ref<float> _r0(_grad0 *= _d_xNDC);
        _d_V += _r0;
        clad::array_ref<float> _r1(_grad1 *= _d_xNDC);
        _d_projM += _r1;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
  
  CamInfo data = {
                    {1.0f, 0.3f, 0.2f, 0.1f,
                     0.3f, 1.0f, 0.1f, 0.1f,
                     0.2f, 0.2f, 1.0f, 0.1f,
                     0.1f, 0.1f, 0.1f, 1.0f},
                     1024.0f, 
                     1024.0f };

  std::cout << "HERE(1)" << std::endl;

  auto vsx_grad = clad::gradient(VS_X);

  std::cout << "HERE(2)" << std::endl;
  
  constexpr int ARRSIZE = 16+3+1;
  float vertex[3] = {1,1,1};
  float result1[ARRSIZE] = {};

  volatile float dontIgnoreMe = 0.0f;
  
  auto before = std::chrono::high_resolution_clock::now();
  
  for(int i=0;i<1000000;i++)
  {
    for(int j=0;j<ARRSIZE;j++)
      result1[j] = 0.0f;
    dontIgnoreMe = 0.0f;

    VS_X_grad_v2(vertex, data.projM, data.width, 
                 clad::array_ref<float>(&result1[0], 3), 
                 clad::array_ref<float>(&result1[3], 16),
                 clad::array_ref<float>(&result1[19], 1));

    //vsx_grad.execute(data.projM, vertex, data.width,
    //                 clad::array_ref<float>(&result1[0], 3), clad::array_ref<float>(&result1[3], 16), clad::array_ref<float>(&result1[19], 1));
 
    for(int j=0;j<ARRSIZE;j++)
      dontIgnoreMe += result1[j];
  }

  float timeMs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

  std::cout << std::endl;
  std::cout << "timeMs = " << timeMs << std::endl;
  std::cout << std::endl;

  for(int i=0;i<21;i++)
    std::cout << i << ":\t" << result1[i] << std::endl;
  std::cout << "all summ = " << dontIgnoreMe << std::endl;

  return 0;
}
