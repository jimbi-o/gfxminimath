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
class matrix {
 public:
  matrix(const float m00, const float m01, const float m02, const float m03,
         const float m10, const float m11, const float m12, const float m13,
         const float m20, const float m21, const float m22, const float m23,
         const float m30, const float m31, const float m32, const float m33)
      : m0(m00, m10, m20, m30)
      , m1(m01, m11, m21, m31)
      , m2(m02, m12, m22, m32)
      , m3(m03, m13, m23, m33) {
  }
  vec4 m0, m1, m2, m3;
};
inline auto mul(const matrix& m, const vec4& v) {
  vec4 a = m.m0 * v;
  vec4 b = m.m1 * v;
  vec4 c = m.m2 * v;
  vec4 d = m.m3 * v;
  float x = horizontal_add(a);
  float y = horizontal_add(b);
  float z = horizontal_add(c);
  float w = horizontal_add(d);
  return vec4(x, y, z, w);
}
inline void to_array(const vec4& src, float dst[4]) {
  src.store(dst);
}
// https://shikihuiku.github.io/post/projection_matrix/
inline auto perspective_division(const vec4& v) {
  vec4 w = permute4<3,3,3,3>(v);
  return v * approx_recipr(w);
}
}
#endif
