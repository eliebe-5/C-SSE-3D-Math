#include <math.h>

typedef struct
{
  float x;
  float y;
} v2;

typedef struct
{
  float x;
  float y;
  float z;
} v3;

typedef struct
{
  float x;
  float y;
  float z;
  float w;
} v4;

static inline v4 v3_to_v4(v3 one) { v4 res; res.x = one.x; res.y = one.y; res.z = one.z; res.w = 1; return res; }

static inline v3 v4_to_v3(v4 one) { v3 res; res.x = one.x; res.y = one.y; res.z = one.z; return res; }


static inline v2 add_v2(v2 one, v2 two) { v2 res; res.x = one.x + two.x; res.y = one.y + two.y; return res; }

static inline v2 sub_v2(v2 one, v2 two) { v2 res; res.x = one.x - two.x; res.y = one.y - two.y; return res; }

static inline v2 mult_v2_f(v2 one, float two) { v2 res; res.x = one.x * two; res.y = one.y * two; return res; }

static inline float dot_v2(v2 one, v2 two) { float res; res = one.x * two.x + one.y * two.y; return res; }

static inline v2 div_v2_f(v2 one, float two) { v2 res; res.x = one.x / two; res.y = one.y / two; return res; }

static inline float mag_v2(v2 one) { float res; res = (float)sqrt(one.x*one.x + one.y*one.y);  return res; }

static inline v3 add_v3(v3 one, v3 two) { v3 res; res.x = one.x + two.x; res.y = one.y + two.y; res.z = one.z + two.z; return res; }

static inline v3 sub_v3(v3 one, v3 two) { v3 res; res.x = one.x - two.x; res.y = one.y - two.y; res.z = one.z - two.z; return res; }

static inline v3 mult_v3_f(v3 one, float two) { v3 res; res.x = one.x * two; res.y = one.y * two; res.z = one.z * two; return res; }

static inline float dot_v3(v3 one, v3 two) { float res; res = one.x * two.x + one.y * two.y + one.z * two.z; return res; }

static inline v3 cross_v3(v3 one, v3 two) { v3 res; res.x = one.y*two.z - one.z*two.y; res.y = one.z*two.x - one.x*two.z; res.y = one.x*two.y - one.y*two.x; return res; }

static inline v3 div_v3_f(v3 one, float two) { v3 res; res.x = one.x / two; res.y = one.y / two; res.z = one.z / two; return res; }

static inline float mag_v3(v3 one) { float res; res = (float)sqrt(one.x*one.x + one.y*one.y + one.z*one.z);  return res; }

static inline v4 add_v4(v4 one, v4 two) { v4 res; res.x = one.x + two.x; res.y = one.y + two.y; res.z = one.z + two.z; res.w = one.w + two.w; return res; }

static inline v4 sub_v4(v4 one, v4 two) { v4 res; res.x = one.x - two.x; res.y = one.y - two.y; res.z = one.z - two.z; res.w = one.w - two.w; return res; }

static inline v4 mult_v4_f(v4 one, float two) { v4 res; res.x = one.x * two; res.y = one.y * two; res.z = one.z * two; res.w = one.w * two; return res; }

static inline float dot_v4(v4 one, v4 two) { float res; res = one.x * two.x + one.y * two.y + one.z * two.z + one.w * two.w; return res; }

static inline v4 div_v4_f(v4 one, float two) { v4 res; res.x = one.x / two; res.y = one.y / two; res.z = one.z / two; res.w = one.w / two; return res; }

static inline float mag_v4(v4 one) { float res; res = (float)sqrt(one.x*one.x + one.y*one.y + one.z*one.z + one.w*one.w);  return res; }
