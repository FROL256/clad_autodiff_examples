static inline void maxD_grad(float x, float y, clad::array_ref<float> _d_x, clad::array_ref<float> _d_y) {
    bool _cond0;
    _cond0 = x < y;
    float maxD_return = _cond0 ? y : x;
    goto _label0;
  _label0:
    if (_cond0)
        * _d_y += 1;
    else
        * _d_x += 1;
}
static inline void minD_grad(float x, float y, clad::array_ref<float> _d_x, clad::array_ref<float> _d_y) {
    bool _cond0;
    _cond0 = x < y;
    float minD_return = _cond0 ? x : y;
    goto _label0;
  _label0:
    if (_cond0)
        * _d_x += 1;
    else
        * _d_y += 1;
}
static inline void clampD_grad(float x, float a_min, float a_max, clad::array_ref<float> _d_x, clad::array_ref<float> _d_a_min, clad::array_ref<float> _d_a_max) {
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    _t0 = a_max;
    _t1 = x;
    _t2 = a_min;
    _t3 = maxD(_t1, _t2);
    float clampD_return = minD(_t0, _t3);
    goto _label0;
  _label0:
    {
        float _grad2 = 0.F;
        float _grad3 = 0.F;
        minD_grad(_t0, _t3, &_grad2, &_grad3);
        float _r0 = 1 * _grad2;
        * _d_a_max += _r0;
        float _r1 = 1 * _grad3;
        float _grad0 = 0.F;
        float _grad1 = 0.F;
        maxD_grad(_t1, _t2, &_grad0, &_grad1);
        float _r2 = _r1 * _grad0;
        * _d_x += _r2;
        float _r3 = _r1 * _grad1;
        * _d_a_min += _r3;
    }
}
static inline void GGX_Distribution_grad(float cosThetaNH, float alpha, clad::array_ref<float> _d_cosThetaNH, clad::array_ref<float> _d_alpha) {
    float _t0;
    float _t1;
    float _d_alpha2 = 0;
    float _t2;
    float _t3;
    float _t4;
    float _d_NH_sqr = 0;
    float _t5;
    float _t6;
    float _d_den = 0;
    float _t7;
    float _t8;
    float _t9;
    float _t10;
    float _t11;
    float _t12;
    float _t13;
    _t1 = alpha;
    _t0 = alpha;
    const float alpha2 = _t1 * _t0;
    _t3 = cosThetaNH;
    _t2 = cosThetaNH;
    _t4 = _t3 * _t2;
    const float NH_sqr = clampD(_t4, 0.F, 1.F);
    _t6 = NH_sqr;
    _t5 = alpha2;
    const float den = _t6 * _t5 + (1.F - NH_sqr);
    _t8 = alpha2;
    _t11 = M_PI;
    _t10 = den;
    _t12 = _t11 * _t10;
    _t9 = den;
    _t13 = _t12 * _t9;
    _t7 = maxD(_t13, 9.99999997E-7F);
    float GGX_Distribution_return = _t8 / _t7;
    goto _label0;
  _label0:
    {
        float _r9 = 1 / _t7;
        _d_alpha2 += _r9;
        float _r10 = 1 * -_t8 / (_t7 * _t7);
        float _grad3 = 0.F;
        float _grad4 = 0.F;
        maxD_grad(_t13, 9.99999997E-7F, &_grad3, &_grad4);
        float _r11 = _r10 * _grad3;
        float _r12 = _r11 * _t9;
        float _r13 = _r12 * _t10;
        float _r14 = _t11 * _r12;
        _d_den += _r14;
        float _r15 = _t12 * _r11;
        _d_den += _r15;
        float _r16 = _r10 * _grad4;
    }
    {
        float _r7 = _d_den * _t5;
        _d_NH_sqr += _r7;
        float _r8 = _t6 * _d_den;
        _d_alpha2 += _r8;
        _d_NH_sqr += -_d_den;
    }
    {
        float _grad0 = 0.F;
        float _grad1 = 0.F;
        float _grad2 = 0.F;
        clampD_grad(_t4, 0.F, 1.F, &_grad0, &_grad1, &_grad2);
        float _r2 = _d_NH_sqr * _grad0;
        float _r3 = _r2 * _t2;
        * _d_cosThetaNH += _r3;
        float _r4 = _t3 * _r2;
        * _d_cosThetaNH += _r4;
        float _r5 = _d_NH_sqr * _grad1;
        float _r6 = _d_NH_sqr * _grad2;
    }
    {
        float _r0 = _d_alpha2 * _t0;
        * _d_alpha += _r0;
        float _r1 = _t1 * _d_alpha2;
        * _d_alpha += _r1;
    }
}
static inline void GGX_GeomShadMask_grad(const float cosThetaN, const float alpha, clad::array_ref<float> _d_cosThetaN, clad::array_ref<float> _d_alpha) {
    float _t0;
    float _t1;
    float _t2;
    float _d_cosTheta_sqr = 0;
    float _t3;
    float _t4;
    float _t5;
    float _d_tan2 = 0;
    float _t6;
    float _t7;
    float _t8;
    float _t9;
    float _t10;
    float _t11;
    float _d_GP = 0;
    _t1 = cosThetaN;
    _t0 = cosThetaN;
    _t2 = _t1 * _t0;
    const float cosTheta_sqr = clampD(_t2, 0.F, 1.F);
    _t4 = (1.F - cosTheta_sqr);
    _t5 = cosTheta_sqr;
    _t3 = maxD(_t5, 9.99999997E-7F);
    const float tan2 = _t4 / _t3;
    _t9 = alpha;
    _t8 = alpha;
    _t10 = _t9 * _t8;
    _t7 = tan2;
    _t11 = 1.F + _t10 * _t7;
    _t6 = (1.F + std::sqrt(_t11));
    const float GP = 2.F / _t6;
    float GGX_GeomShadMask_return = GP;
    goto _label0;
  _label0:
    _d_GP += 1;
    {
        float _r9 = _d_GP / _t6;
        float _r10 = _d_GP * -2.F / (_t6 * _t6);
        float _r11 = _r10 * custom_derivatives::sqrt_darg0(_t11);
        float _r12 = _r11 * _t7;
        float _r13 = _r12 * _t8;
        * _d_alpha += _r13;
        float _r14 = _t9 * _r12;
        * _d_alpha += _r14;
        float _r15 = _t10 * _r11;
        _d_tan2 += _r15;
    }
    {
        float _r5 = _d_tan2 / _t3;
        _d_cosTheta_sqr += -_r5;
        float _r6 = _d_tan2 * -_t4 / (_t3 * _t3);
        float _grad3 = 0.F;
        float _grad4 = 0.F;
        maxD_grad(_t5, 9.99999997E-7F, &_grad3, &_grad4);
        float _r7 = _r6 * _grad3;
        _d_cosTheta_sqr += _r7;
        float _r8 = _r6 * _grad4;
    }
    {
        float _grad0 = 0.F;
        float _grad1 = 0.F;
        float _grad2 = 0.F;
        clampD_grad(_t2, 0.F, 1.F, &_grad0, &_grad1, &_grad2);
        float _r0 = _d_cosTheta_sqr * _grad0;
        float _r1 = _r0 * _t0;
        * _d_cosThetaN += _r1;
        float _r2 = _t1 * _r0;
        * _d_cosThetaN += _r2;
        float _r3 = _d_cosTheta_sqr * _grad1;
        float _r4 = _d_cosTheta_sqr * _grad2;
    }
}
static inline void EvalGGX_grad(float l[3], float v[3], float n[3], float roughness, clad::array_ref<float> _d_l, clad::array_ref<float> _d_v, clad::array_ref<float> _d_n, clad::array_ref<float> _d_roughness) {
    float _d_h[3] = {};
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    float _t4;
    float _t5;
    float _t6;
    float _t7;
    float _d_lenInv = 0;
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
    float _d_dotNH = 0;
    float _t20;
    float _t21;
    float _t22;
    float _t23;
    float _t24;
    float _t25;
    float _d_dotNV = 0;
    float _t26;
    float _t27;
    float _t28;
    float _t29;
    float _t30;
    float _t31;
    float _d_dotNL = 0;
    float _t32;
    float _t33;
    float _d_roughSqr = 0;
    float _t34;
    float _t35;
    float _d_D = 0;
    float _t36;
    float _t37;
    float _t38;
    float _t39;
    float _t40;
    float _t41;
    float _d_G = 0;
    float _t42;
    float _t43;
    float _t44;
    float _t45;
    float _t46;
    float _t47;
    float _t48;
    float _t49;
    float h[3];
    {
        h[0] = l[0] + v[0];
        h[1] = l[1] + v[1];
        h[2] = l[2] + v[2];
        _t2 = h[0];
        _t1 = h[0];
        _t4 = h[1];
        _t3 = h[1];
        _t6 = h[2];
        _t5 = h[2];
        _t7 = _t2 * _t1 + _t4 * _t3 + _t6 * _t5;
        _t0 = std::sqrt(_t7);
        const float lenInv = 1.F / _t0;
        _t9 = h[0];
        _t8 = lenInv;
        h[0] *= _t8;
        _t11 = h[1];
        _t10 = lenInv;
        h[1] *= _t10;
        _t13 = h[2];
        _t12 = lenInv;
        h[2] *= _t12;
    }
    _t15 = n[0];
    _t14 = h[0];
    _t17 = n[1];
    _t16 = h[1];
    _t19 = n[2];
    _t18 = h[2];
    const float dotNH = _t15 * _t14 + _t17 * _t16 + _t19 * _t18;
    _t21 = n[0];
    _t20 = v[0];
    _t23 = n[1];
    _t22 = v[1];
    _t25 = n[2];
    _t24 = v[2];
    const float dotNV = _t21 * _t20 + _t23 * _t22 + _t25 * _t24;
    _t27 = n[0];
    _t26 = l[0];
    _t29 = n[1];
    _t28 = l[1];
    _t31 = n[2];
    _t30 = l[2];
    const float dotNL = _t27 * _t26 + _t29 * _t28 + _t31 * _t30;
    _t33 = roughness;
    _t32 = roughness;
    const float roughSqr = _t33 * _t32;
    _t34 = dotNH;
    _t35 = roughSqr;
    const float D = GGX_Distribution(_t34, _t35);
    _t37 = dotNV;
    _t38 = roughSqr;
    _t39 = GGX_GeomShadMask(_t37, _t38);
    _t40 = dotNL;
    _t41 = roughSqr;
    _t36 = GGX_GeomShadMask(_t40, _t41);
    const float G = _t39 * _t36;
    _t44 = D;
    _t43 = G;
    _t45 = (_t44 * _t43);
    _t47 = dotNV;
    _t48 = 4.F * _t47;
    _t46 = dotNL;
    _t49 = _t48 * _t46;
    _t42 = maxD(_t49, 9.99999997E-7F);
    float EvalGGX_return = _t45 / _t42;
    goto _label0;
  _label0:
    {
        float _r40 = 1 / _t42;
        float _r41 = _r40 * _t43;
        _d_D += _r41;
        float _r42 = _t44 * _r40;
        _d_G += _r42;
        float _r43 = 1 * -_t45 / (_t42 * _t42);
        float _grad6 = 0.F;
        float _grad7 = 0.F;
        maxD_grad(_t49, 9.99999997E-7F, &_grad6, &_grad7);
        float _r44 = _r43 * _grad6;
        float _r45 = _r44 * _t46;
        float _r46 = _r45 * _t47;
        float _r47 = 4.F * _r45;
        _d_dotNV += _r47;
        float _r48 = _t48 * _r44;
        _d_dotNL += _r48;
        float _r49 = _r43 * _grad7;
    }
    {
        float _r34 = _d_G * _t36;
        float _grad2 = 0.F;
        float _grad3 = 0.F;
        GGX_GeomShadMask_grad(_t37, _t38, &_grad2, &_grad3);
        float _r35 = _r34 * _grad2;
        _d_dotNV += _r35;
        float _r36 = _r34 * _grad3;
        _d_roughSqr += _r36;
        float _r37 = _t39 * _d_G;
        float _grad4 = 0.F;
        float _grad5 = 0.F;
        GGX_GeomShadMask_grad(_t40, _t41, &_grad4, &_grad5);
        float _r38 = _r37 * _grad4;
        _d_dotNL += _r38;
        float _r39 = _r37 * _grad5;
        _d_roughSqr += _r39;
    }
    {
        float _grad0 = 0.F;
        float _grad1 = 0.F;
        GGX_Distribution_grad(_t34, _t35, &_grad0, &_grad1);
        float _r32 = _d_D * _grad0;
        _d_dotNH += _r32;
        float _r33 = _d_D * _grad1;
        _d_roughSqr += _r33;
    }
    {
        float _r30 = _d_roughSqr * _t32;
        * _d_roughness += _r30;
        float _r31 = _t33 * _d_roughSqr;
        * _d_roughness += _r31;
    }
    {
        float _r24 = _d_dotNL * _t26;
        _d_n[0] += _r24;
        float _r25 = _t27 * _d_dotNL;
        _d_l[0] += _r25;
        float _r26 = _d_dotNL * _t28;
        _d_n[1] += _r26;
        float _r27 = _t29 * _d_dotNL;
        _d_l[1] += _r27;
        float _r28 = _d_dotNL * _t30;
        _d_n[2] += _r28;
        float _r29 = _t31 * _d_dotNL;
        _d_l[2] += _r29;
    }
    {
        float _r18 = _d_dotNV * _t20;
        _d_n[0] += _r18;
        float _r19 = _t21 * _d_dotNV;
        _d_v[0] += _r19;
        float _r20 = _d_dotNV * _t22;
        _d_n[1] += _r20;
        float _r21 = _t23 * _d_dotNV;
        _d_v[1] += _r21;
        float _r22 = _d_dotNV * _t24;
        _d_n[2] += _r22;
        float _r23 = _t25 * _d_dotNV;
        _d_v[2] += _r23;
    }
    {
        float _r12 = _d_dotNH * _t14;
        _d_n[0] += _r12;
        float _r13 = _t15 * _d_dotNH;
        _d_h[0] += _r13;
        float _r14 = _d_dotNH * _t16;
        _d_n[1] += _r14;
        float _r15 = _t17 * _d_dotNH;
        _d_h[1] += _r15;
        float _r16 = _d_dotNH * _t18;
        _d_n[2] += _r16;
        float _r17 = _t19 * _d_dotNH;
        _d_h[2] += _r17;
    }
    {
        {
            float _r_d5 = _d_h[2];
            _d_h[2] += _r_d5 * _t12;
            float _r11 = _t13 * _r_d5;
            _d_lenInv += _r11;
            _d_h[2] -= _r_d5;
        }
        {
            float _r_d4 = _d_h[1];
            _d_h[1] += _r_d4 * _t10;
            float _r10 = _t11 * _r_d4;
            _d_lenInv += _r10;
            _d_h[1] -= _r_d4;
        }
        {
            float _r_d3 = _d_h[0];
            _d_h[0] += _r_d3 * _t8;
            float _r9 = _t9 * _r_d3;
            _d_lenInv += _r9;
            _d_h[0] -= _r_d3;
        }
        {
            float _r0 = _d_lenInv / _t0;
            float _r1 = _d_lenInv * -1.F / (_t0 * _t0);
            float _r2 = _r1 * custom_derivatives::sqrt_darg0(_t7);
            float _r3 = _r2 * _t1;
            _d_h[0] += _r3;
            float _r4 = _t2 * _r2;
            _d_h[0] += _r4;
            float _r5 = _r2 * _t3;
            _d_h[1] += _r5;
            float _r6 = _t4 * _r2;
            _d_h[1] += _r6;
            float _r7 = _r2 * _t5;
            _d_h[2] += _r7;
            float _r8 = _t6 * _r2;
            _d_h[2] += _r8;
        }
        {
            float _r_d2 = _d_h[2];
            _d_l[2] += _r_d2;
            _d_v[2] += _r_d2;
            _d_h[2] -= _r_d2;
        }
        {
            float _r_d1 = _d_h[1];
            _d_l[1] += _r_d1;
            _d_v[1] += _r_d1;
            _d_h[1] -= _r_d1;
        }
        {
            float _r_d0 = _d_h[0];
            _d_l[0] += _r_d0;
            _d_v[0] += _r_d0;
            _d_h[0] -= _r_d0;
        }
    }
}
