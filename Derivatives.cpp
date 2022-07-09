void VS_Y_grad(float V[3], const Uniforms &data, clad::array_ref<float> _d_V, clad::array_ref<float> _d_data) {
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    float _t4;
    float _t5;
    float _d_W = 0;
    float _t6;
    float _t7;
    float _d_xNDC = 0;
    float _t8;
    float _t9;
    _t1 = V[0];
    _t0 = data.projM[3];
    _t3 = V[1];
    _t2 = data.projM[7];
    _t5 = V[2];
    _t4 = data.projM[11];
    const float W = _t1 * _t0 + _t3 * _t2 + _t5 * _t4 + data.projM[15];
    _t7 = V[1];
    _t6 = W;
    const float xNDC = _t7 / _t6;
    _t9 = (xNDC * 0.5F + 0.5F);
    _t8 = data.height;
    float VS_Y_return = _t9 * _t8 - 0.5F;
    goto _label0;
  _label0:
    {
        float _r8 = 1 * _t8;
        float _r9 = _r8 * 0.5F;
        _d_xNDC += _r9;
        float _r10 = _t9 * 1;
    }
    {
        float _r6 = _d_xNDC / _t6;
        _d_V[1] += _r6;
        float _r7 = _d_xNDC * -_t7 / (_t6 * _t6);
        _d_W += _r7;
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
