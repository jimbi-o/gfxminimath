#ifndef GFX_MINI_MATH_H
#define GFX_MINI_MATH_H
#include "vectorclass.h"
#include "vectormath_exp.h"
#include "vectormath_hyp.h"
#include "vectormath_trig.h"
#include "quaternion/quaternion.h"
#include "vector3d/vector3d.h"
namespace gfxminimath {
using vec4 = vcl::Vec4f;
using vec3 = vcl::Vec3Df;
using quat = vcl::Quaternion1f;
using quat = vcl::Quaternion1f;
using matrix = vcl::Vec16f;
inline auto mul(const vec4& v, const matrix& m) {
  return v;
}
inline void GetValue(const vec4& src, float dst[4]) {
  src.store(dst);
}
}
#endif
