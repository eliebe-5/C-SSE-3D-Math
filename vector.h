#include <math.h>
#include <xmmintrin.h>
#include <smmintrin.h>


typedef struct
{
  float x;
  float y;
  float z;
  float w;
} v4;

union xmm_v4
{
	v4 v;
	__m128 sse;
};

//static inline v4 add_v4(v4 one, v4 two) { v4 res; res.x = one.x + two.x; res.y = one.y + two.y; res.z = one.z + two.z; res.w = one.w + two.w; return res; }

static inline __m128 set_v4(float x, float y, float z, float w) { return _mm_setr_ps(x, y, z, w); };

static inline __m128 add_v4(__m128 one, __m128 two) { return _mm_add_ps(one, two); }

static inline __m128 sub_v4(__m128 one, __m128 two) { return _mm_sub_ps(one, two); }

static inline __m128 mult_v4_f(__m128 one, const float two) { return _mm_mul_ps(one, _mm_load_ps1(&two)); }

static inline float dot_v4(__m128 one, __m128 two) { _mm_cvtss_f32(_mm_dp_ps(one, two, 0x71)); }

static inline __m128 div_v4_f(__m128 one, const float two) { const float div = 1 / two; return _mm_mul_ps(one, _mm_load_ps1(&div)); }

static inline float mag_v4(__m128 one) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(one, one, 0x71))); }
