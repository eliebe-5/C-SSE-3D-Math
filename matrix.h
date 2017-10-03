#include <math.h>
#include <xmmintrin.h>

typedef struct
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
} m4x4;

typedef struct
{
	__m128 xmm0, xmm1, xmm2, xmm3;
} _m128x4;

union xmm_m4x4
{
	m4x4 m;
	_m128x4 sse;
};

static inline _m128x4 identity_m4x4()
{
	_m128x4 res;

	res.xmm0 = _mm_setr_ps(1.f, 0.f, 0.f, 0.f);
	res.xmm1 = _mm_setr_ps(0.f, 1.f, 0.f, 0.f);
	res.xmm2 = _mm_setr_ps(0.f, 0.f, 1.f, 0.f);
	res.xmm3 = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
	
	return res;
}

static inline m4x4 mult_m4x4(m4x4 one, m4x4 two)
{
	m4x4 res;

	res.m00 = one.m00*two.m00 + one.m01*two.m10 + one.m02*two.m20 + one.m03*two.m30;
	res.m10 = one.m10*two.m00 + one.m11*two.m10 + one.m12*two.m20 + one.m13*two.m30;
	res.m20 = one.m20*two.m00 + one.m21*two.m10 + one.m22*two.m20 + one.m23*two.m30;
	res.m30 = one.m30*two.m00 + one.m31*two.m10 + one.m32*two.m20 + one.m33*two.m30;

	res.m01 = one.m00*two.m01 + one.m01*two.m11 + one.m02*two.m21 + one.m03*two.m31;
	res.m11 = one.m10*two.m01 + one.m11*two.m11 + one.m12*two.m21 + one.m13*two.m31;
	res.m21 = one.m20*two.m01 + one.m21*two.m11 + one.m22*two.m21 + one.m23*two.m31;
	res.m31 = one.m30*two.m01 + one.m31*two.m11 + one.m32*two.m21 + one.m33*two.m31;

	res.m02 = one.m00*two.m02 + one.m01*two.m12 + one.m02*two.m22 + one.m03*two.m32;
	res.m12 = one.m10*two.m02 + one.m11*two.m12 + one.m12*two.m22 + one.m13*two.m32;
	res.m22 = one.m20*two.m02 + one.m21*two.m12 + one.m22*two.m22 + one.m23*two.m32;
	res.m32 = one.m30*two.m02 + one.m31*two.m12 + one.m32*two.m22 + one.m33*two.m32;

	res.m03 = one.m00*two.m03 + one.m01*two.m13 + one.m02*two.m23 + one.m03*two.m33;
	res.m13 = one.m10*two.m03 + one.m11*two.m13 + one.m12*two.m23 + one.m13*two.m33;
	res.m23 = one.m20*two.m03 + one.m21*two.m13 + one.m22*two.m23 + one.m23*two.m33;
	res.m33 = one.m30*two.m03 + one.m31*two.m13 + one.m32*two.m23 + one.m33*two.m33;

	return res;
}

static inline m4x4 transpose_m4x4(m4x4 one)
{
	m4x4 res;

	res.m00 = one.m00; res.m01 = one.m10; res.m02 = one.m20; res.m03 = one.m30;
	res.m10 = one.m01; res.m11 = one.m11; res.m12 = one.m21; res.m13 = one.m31;
	res.m20 = one.m02; res.m21 = one.m12; res.m22 = one.m22; res.m23 = one.m32;
	res.m30 = one.m03; res.m31 = one.m13; res.m32 = one.m23; res.m33 = one.m33;

	return res;
}

static inline m4x4 rot_m4x4(float x, float y, float z)
{
	m4x4 res;
	m4x4 mx;
	m4x4 my;
	m4x4 mz;

	mx = identity_m4x4();
	my = identity_m4x4();
	mz = identity_m4x4();

	mx.m11 = cos(x); mx.m12 = -sin(x); mx.m21 = sin(x); mx.m22 = cos(x);
	my.m00 = cos(y); my.m02 = sin(y); my.m02 = -sin(y); my.m22 = cos(y);
	mz.m00 = cos(z); mz.m01 = -sin(z); mz.m01 = sin(z); mx.m11 = cos(z);

	res = mult_m4x4(mult_m4x4(mx, my), mz);

	return res;
}

static inline m4x4 translation_m4x4(float x, float y, float z)
{
	m4x4 res;

	res = identity_m4x4();
	res.m03 = x;
	res.m13 = y;
	res.m23 = z;

	return res;
}
