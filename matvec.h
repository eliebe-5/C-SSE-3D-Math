#include "vector.h"
#include "matrix.h"


static inline v3 transform_v3(m4x4 one, v3 two)
{
  v3 res;

  res.x = one.m00*two.x + one.m01*two.y + one.m02*two.z + one.m03*1;
  res.y = one.m10*two.x + one.m11*two.y + one.m12*two.z + one.m13*1;
  res.z = one.m20*two.x + one.m21*two.y + one.m22*two.z + one.m23*1;
  
  return res;
}

static inline v4 transform_v4(m4x4 one, v4 two)
{
  v4 res;

  res.x = one.m00*two.x + one.m01*two.y + one.m02*two.z + one.m03*two.w;
  res.y = one.m10*two.x + one.m11*two.y + one.m12*two.z + one.m13*two.w;
  res.z = one.m20*two.x + one.m21*two.y + one.m22*two.z + one.m23*two.w;
  res.w = one.m30*two.x + one.m31*two.y + one.m32*two.z + one.m33*two.w;
  
  return res;
}
