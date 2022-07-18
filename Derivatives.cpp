static inline void VS_Y_grad(float V[3], const CamInfo &data, clad::array_ref<float> _d_V, clad::array_ref<float> _d_data) {
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
    goto _label0;
  _label0:
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
