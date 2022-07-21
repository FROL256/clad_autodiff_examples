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

void h(float a, float b, float output[]) {
  output[0] = a * a * a;
  output[1] = a * a * a + b * b * b;
  output[2] = 2 * (a + b);
}

struct CamInfo
{
  float projM[16];
  float width;
  float height;
};

//void VertexShader(const CamInfo& u, float vx, float vy, float vz, 
//                  float output[2])
//{
//  const float W    =   vx * u.projM[3] + vy * u.projM[7] + vz * u.projM[11] + u.projM[15]; 
//  const float xNDC =  (vx * u.projM[0] + vy * u.projM[4] + vz * u.projM[ 8] + u.projM[12])/W;
//  const float yNDC = -(vx * u.projM[1] + vy * u.projM[5] + vz * u.projM[ 9] + u.projM[13])/W;
//  output[0] = (xNDC*0.5f + 0.5f)*u.width;
//  output[1] = (yNDC*0.5f + 0.5f)*u.height; 
//}

static inline void VertexShader(const CamInfo& u, float vx, float vy, float vz, 
                                float output[2])
{
  const float W    =   vx * u.projM[3] + vy * u.projM[7] + vz * u.projM[11] + u.projM[15]; 
  output[0] = (((vx * u.projM[0] + vy * u.projM[4] + vz * u.projM[ 8] + u.projM[12])/W)*0.5f + 0.5f)*u.width;
  output[1] = ((-(vx * u.projM[1] + vy * u.projM[5] + vz * u.projM[ 9] + u.projM[13])/W)*0.5f + 0.5f)*u.height; 
}

void VertexShader_jac(const CamInfo &u, float vx, float vy, float vz, float output[2], float *jacobianMatrix) 
{
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
    float _t14;
    float _t15;
    float _t16;
    float _t17;
    float _t18;
    float _t19;
    float _t20;
    float _t21;
    float _t22;
    float _t23;
    float _t24;
    float _t25;
    _t1 = vx;
    _t0 = u.projM[3];
    _t3 = vy;
    _t2 = u.projM[7];
    _t5 = vz;
    _t4 = u.projM[11];
    const float W = _t1 * _t0 + _t3 * _t2 + _t5 * _t4 + u.projM[15];
    _t9 = vx;
    _t8 = u.projM[0];
    _t11 = vy;
    _t10 = u.projM[4];
    _t13 = vz;
    _t12 = u.projM[8];
    _t14 = (_t9 * _t8 + _t11 * _t10 + _t13 * _t12 + u.projM[12]);
    _t7 = W;
    _t15 = ((_t14 / _t7) * 0.5F + 0.5F);
    _t6 = u.width;
    output[0] = (((vx * u.projM[0] + vy * u.projM[4] + vz * u.projM[8] + u.projM[12]) / W) * 0.5F + 0.5F) * u.width;
    _t19 = vx;
    _t18 = u.projM[1];
    _t21 = vy;
    _t20 = u.projM[5];
    _t23 = vz;
    _t22 = u.projM[9];
    _t24 = -(_t19 * _t18 + _t21 * _t20 + _t23 * _t22 + u.projM[13]);
    _t17 = W;
    _t25 = ((_t24 / _t17) * 0.5F + 0.5F);
    _t16 = u.height;
    output[1] = ((-(vx * u.projM[1] + vy * u.projM[5] + vz * u.projM[9] + u.projM[13]) / W) * 0.5F + 0.5F) * u.height;
    {
        float _r17 = 1 * _t16;
        float _r18 = _r17 * 0.5F;
        float _r19 = _r18 / _t17;
        float _r20 = -_r19 * _t18;
        jacobianMatrix[3UL] += _r20;
        float _r21 = _t19 * -_r19;
        float _r22 = -_r19 * _t20;
        jacobianMatrix[4UL] += _r22;
        float _r23 = _t21 * -_r19;
        float _r24 = -_r19 * _t22;
        jacobianMatrix[5UL] += _r24;
    }
    {
        float _r6 = 1 * _t6;
        float _r7 = _r6 * 0.5F;
        float _r8 = _r7 / _t7;
        float _r9 = _r8 * _t8;
        jacobianMatrix[0UL] += _r9;
        float _r10 = _t9 * _r8;
        float _r11 = _r8 * _t10;
        jacobianMatrix[1UL] += _r11;
        float _r12 = _t11 * _r8;
        float _r13 = _r8 * _t12;
        jacobianMatrix[2UL] += _r13;
    }
}


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

static inline void VS_X_grad(float V[3], const CamInfo &data, float _d_V[3]) {
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
    _t0 = data.projM[3];
    _t3 = V[1];
    _t2 = data.projM[7];
    _t5 = V[2];
    _t4 = data.projM[11];
    const float W = _t1 * _t0 + _t3 * _t2 + _t5 * _t4 + data.projM[15];
    _t8 = V[0];
    _t7 = data.projM[0];
    _t10 = V[1];
    _t9 = data.projM[4];
    _t12 = V[2];
    _t11 = data.projM[8];
    _t13 = (_t8 * _t7 + _t10 * _t9 + _t12 * _t11 + data.projM[12]);
    _t6 = W;
    const float xNDC = _t13 / _t6;
    _t15 = (xNDC * 0.5F + 0.5F);
    _t14 = data.width;
    float VS_X_return = _t15 * _t14;
    {
        float _r14 = 1 * _t14;
        float _r15 = _r14 * 0.5F;
        _d_xNDC += _r15;
        float _r16 = _t15 * 1;
    }
    {
        float _r6 = _d_xNDC / _t6;
        float _r7 = _r6 * _t7;
        _d_V[0] += _r7;
        float _r8 = _t8 * _r6;
        float _r9 = _r6 * _t9;
        _d_V[1] += _r9;
        float _r10 = _t10 * _r6;
        float _r11 = _r6 * _t11;
        _d_V[2] += _r11;
        float _r12 = _t12 * _r6;
        float _r13 = _d_xNDC * -_t13 / (_t6 * _t6);
        _d_W += _r13;
    }
    {
        float _r0 = _d_W * _t0;
        _d_V[0] += _r0;
        float _r1 = _t1 * _d_W;
        float _r2 = _d_W * _t2;
        _d_V[1] += _r2;
        float _r3 = _t3 * _d_W;
        float _r4 = _d_W * _t4;
        _d_V[2] += _r4;
        float _r5 = _t5 * _d_W;
    }
}

static inline void VS_Y_grad(float V[3], const CamInfo &data, float _d_V[3]) {
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
    _t0 = data.projM[3];
    _t3 = V[1];
    _t2 = data.projM[7];
    _t5 = V[2];
    _t4 = data.projM[11];
    const float W = _t1 * _t0 + _t3 * _t2 + _t5 * _t4 + data.projM[15];
    _t8 = V[0];
    _t7 = data.projM[1];
    _t10 = V[1];
    _t9 = data.projM[5];
    _t12 = V[2];
    _t11 = data.projM[9];
    _t13 = -(_t8 * _t7 + _t10 * _t9 + _t12 * _t11 + data.projM[13]);
    _t6 = W;
    const float xNDC = _t13 / _t6;
    _t15 = (xNDC * 0.5F + 0.5F);
    _t14 = data.height;
    float VS_Y_return = _t15 * _t14;
    {
        float _r14 = 1 * _t14;
        float _r15 = _r14 * 0.5F;
        _d_xNDC += _r15;
        float _r16 = _t15 * 1;
    }
    {
        float _r6 = _d_xNDC / _t6;
        float _r7 = -_r6 * _t7;
        _d_V[0] += _r7;
        float _r8 = _t8 * -_r6;
        float _r9 = -_r6 * _t9;
        _d_V[1] += _r9;
        float _r10 = _t10 * -_r6;
        float _r11 = -_r6 * _t11;
        _d_V[2] += _r11;
        float _r12 = _t12 * -_r6;
        float _r13 = _d_xNDC * -_t13 / (_t6 * _t6);
        _d_W += _r13;
    }
    {
        float _r0 = _d_W * _t0;
        _d_V[0] += _r0;
        float _r1 = _t1 * _d_W;
        float _r2 = _d_W * _t2;
        _d_V[1] += _r2;
        float _r3 = _t3 * _d_W;
        float _r4 = _d_W * _t4;
        _d_V[2] += _r4;
        float _r5 = _t5 * _d_W;
    }
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
  CamInfo data = {
                    {1.0f, 0.3f, 0.2f, 0.1f,
                     0.3f, 1.0f, 0.1f, 0.1f,
                     0.2f, 0.2f, 1.0f, 0.1f,
                     0.1f, 0.1f, 0.1f, 1.0f},
                     1024.0f};


  //auto vsx_grad = clad::gradient(VS_Y);
  auto h_jac = clad::jacobian(VertexShader, "vx,vy,vz");

  float3 v0_d[2] = {}; 
  float3 v1_d[2] = {}; 
        
  float3 pos(1,1,1);

  VS_X_grad(pos.M, data, v0_d[0].M);
  VS_Y_grad(pos.M, data, v0_d[1].M);
  
  float temp[2] = {};
  VertexShader_jac(data, pos.x, pos.y, pos.z, temp, v1_d[0].M);

  for(int i=0;i<3;i++)
  {
    std::cout << v0_d[0][i] << "\t" << v1_d[0][i] << std::endl;
    std::cout << v0_d[0][i] << "\t" << v1_d[1][i] << std::endl << std::endl;
  }
  
  //vsx_grad.execute(data.projM, vertex, data.width,
  //                 clad::array_ref<float>(&result1[0], 16), clad::array_ref<float>(&result1[16], 4), clad::array_ref<float>(&result1[20], 1));

  //VS_X_grad(data.projM, vertex, data.viewportWidth,
  //          clad::array_ref<float>(&result1[0], 16), clad::array_ref<float>(&result1[16], 4), clad::array_ref<float>(&result1[20], 1));


 
  return 0;
}
