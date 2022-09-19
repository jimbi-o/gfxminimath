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
// left handed
class matrix {
 public:
  matrix();
  matrix(const vec4& column0, const vec4& column1, const vec4& column2, const vec4& column3); // columns
  matrix(const float m00, const float m01, const float m02, const float m03,
         const float m10, const float m11, const float m12, const float m13,
         const float m20, const float m21, const float m22, const float m23,
         const float m30, const float m31, const float m32, const float m33);
  vec4 m0, m1, m2, m3;
};
vec4 __vectorcall append_w(const vec3& m, const float w);
vec4 __vectorcall mul(const matrix& m, const vec4& v);
matrix __vectorcall transpose(const matrix& m);
matrix __vectorcall lookat(const vec3& from, const vec3& to, const vec3& up_world = vec3(0.0f, 1.0f, 0.0f));
vec3 __vectorcall perspective_division(const vec4& v);
void __vectorcall to_array(const vec4& src, float dst[4]);
void __vectorcall to_array(const vec3& src, float dst[3]);
void __vectorcall to_array_row_major(const matrix& src, float dst[16]);
void __vectorcall to_array_column_major(const matrix& src, float dst[16]);
}
#endif
