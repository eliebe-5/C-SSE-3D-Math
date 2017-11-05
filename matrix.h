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

static inline _m128x4 mult_m4x4(_m128x4 one, _m128x4 two)
{
  _m128x4 res;

  union xmm_m4x4 ass;

  ass.sse = one;

  float *A = &(ass.m.m00);
  __m128 *C = &(res.xmm0);
    
  for(int i = 0; i < 4; i++) {
    __m128 brod1 = _mm_set1_ps(A[4*i + 0]);
    __m128 brod2 = _mm_set1_ps(A[4*i + 1]);
    __m128 brod3 = _mm_set1_ps(A[4*i + 2]);
    __m128 brod4 = _mm_set1_ps(A[4*i + 3]);
    __m128 row = _mm_add_ps(
			    _mm_add_ps(
				       _mm_mul_ps(brod1, two.xmm0),
				       _mm_mul_ps(brod2, two.xmm1)),
			    _mm_add_ps(
				       _mm_mul_ps(brod3, two.xmm2),
				       _mm_mul_ps(brod4, two.xmm3)));
    C[i] = row;
  }
  
  return res;
}

static inline _m128x4 transpose_m4x4(_m128x4 one)
{
  union xmm_m4x4 res;
  union xmm_m4x4 arg;

  arg.sse = one;
  
  res.m.m00 = arg.m.m00; res.m01 = arg.m.m10; res.m02 = arg.m.m20; res.m03 = arg.m.m30;
  res.m.m10 = arg.m.m01; res.m11 = arg.m.m11; res.m12 = arg.m.m21; res.m13 = arg.m.m31;
  res.m.m20 = arg.m.m02; res.m21 = arg.m.m12; res.m22 = arg.m.m22; res.m23 = arg.m.m32;
  res.m.m30 = arg.m.m03; res.m31 = arg.m.m13; res.m32 = arg.m.m23; res.m33 = arg.m.m33;

  return res.sse;
}

static inline _m128x4 rot_m4x4(float x, float y, float z)
{
  _m128x4 res;

  union xmm_m4x4 mx;
  union xmm_m4x4 my;
  union xmm_m4x4 mz;
	
  mx = identity_m4x4();
  my = identity_m4x4();
  mz = identity_m4x4();

  mx.m.m11 = cos(x); mx.m.m12 = -sin(x); mx.m.m21 = sin(x); mx.m.m22 = cos(x);
  my.m.m00 = cos(y); my.m.m02 = sin(y); my.m.m02 = -sin(y); my.m.m22 = cos(y);
  mz.m.m00 = cos(z); mz.m.m01 = -sin(z); mz.m.m01 = sin(z); mx.m.m11 = cos(z);
	
  res = mult_m4x4(mult_m4x4(mx, my), mz);

  return res;
}

static inline _128x4 translation_m4x4(float x, float y, float z)
{
  union xmm_m4x4 res;

  res.sse = identity_m4x4();
  res.m.m03 = x;
  res.m.m13 = y;
  res.m.m23 = z;

  return res.sse;
}
