void h_jac(float a, float b, float jacobianMatrix) {
}
void h_jac(float a, float b, float output[], float *jacobianMatrix) {
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    float _t4;
    float _t5;
    float _t6;
    float _t7;
    float _t8;
    float _t9;
    float _t10;
    float _t11;
    float _t12;
    _t2 = a;
    _t1 = a;
    _t3 = _t2 * _t1;
    _t0 = a;
    output[0] = a * a * a;
    _t6 = a;
    _t5 = a;
    _t7 = _t6 * _t5;
    _t4 = a;
    _t10 = b;
    _t9 = b;
    _t11 = _t10 * _t9;
    _t8 = b;
    output[1] = a * a * a + b * b * b;
    _t12 = (a + b);
    output[2] = 2 * (a + b);
    {
        float _r12 = 1 * _t12;
        float _r13 = 2 * 1;
        jacobianMatrix[4UL] += _r13;
        jacobianMatrix[5UL] += _r13;
    }
    {
        float _r4 = 1 * _t4;
        float _r5 = _r4 * _t5;
        jacobianMatrix[2UL] += _r5;
        float _r6 = _t6 * _r4;
        jacobianMatrix[2UL] += _r6;
        float _r7 = _t7 * 1;
        jacobianMatrix[2UL] += _r7;
        float _r8 = 1 * _t8;
        float _r9 = _r8 * _t9;
        jacobianMatrix[3UL] += _r9;
        float _r10 = _t10 * _r8;
        jacobianMatrix[3UL] += _r10;
        float _r11 = _t11 * 1;
        jacobianMatrix[3UL] += _r11;
    }
    {
        float _r0 = 1 * _t0;
        float _r1 = _r0 * _t1;
        jacobianMatrix[0UL] += _r1;
        float _r2 = _t2 * _r0;
        jacobianMatrix[0UL] += _r2;
        float _r3 = _t3 * 1;
        jacobianMatrix[0UL] += _r3;
    }
}
void h_jac(float a, float b, float output[], float *jacobianMatrix) {
    float _t0;
    float _t1;
    float _t2;
    float _t3;
    float _t4;
    float _t5;
    float _t6;
    float _t7;
    float _t8;
    float _t9;
    float _t10;
    float _t11;
    float _t12;
    _t2 = a;
    _t1 = a;
    _t3 = _t2 * _t1;
    _t0 = a;
    output[0] = a * a * a;
    _t6 = a;
    _t5 = a;
    _t7 = _t6 * _t5;
    _t4 = a;
    _t10 = b;
    _t9 = b;
    _t11 = _t10 * _t9;
    _t8 = b;
    output[1] = a * a * a + b * b * b;
    _t12 = (a + b);
    output[2] = 2 * (a + b);
    {
        float _r12 = 1 * _t12;
        float _r13 = 2 * 1;
        jacobianMatrix[4UL] += _r13;
        jacobianMatrix[5UL] += _r13;
    }
    {
        float _r4 = 1 * _t4;
        float _r5 = _r4 * _t5;
        jacobianMatrix[2UL] += _r5;
        float _r6 = _t6 * _r4;
        jacobianMatrix[2UL] += _r6;
        float _r7 = _t7 * 1;
        jacobianMatrix[2UL] += _r7;
        float _r8 = 1 * _t8;
        float _r9 = _r8 * _t9;
        jacobianMatrix[3UL] += _r9;
        float _r10 = _t10 * _r8;
        jacobianMatrix[3UL] += _r10;
        float _r11 = _t11 * 1;
        jacobianMatrix[3UL] += _r11;
    }
    {
        float _r0 = 1 * _t0;
        float _r1 = _r0 * _t1;
        jacobianMatrix[0UL] += _r1;
        float _r2 = _t2 * _r0;
        jacobianMatrix[0UL] += _r2;
        float _r3 = _t3 * 1;
        jacobianMatrix[0UL] += _r3;
    }
}
