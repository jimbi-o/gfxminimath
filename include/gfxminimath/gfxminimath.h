#ifndef GFX_MINI_MATH_H
#define GFX_MINI_MATH_H
#include <cmath>
#include "vectorclass.h"
#include "vectormath_exp.h"
#include "vectormath_hyp.h"
#include "vectormath_trig.h"
#include "quaternion/quaternion.h"
#include "vector3d/vector3d.h"
namespace gfxminimath {
static const float kPi = static_cast<float>(M_PI);
static const float kHalfPi = kPi / 2.0f;
static const float kInvPi = 1.0f / kPi;
static const float kDegreeToRadian = kPi / 180.0f;
static const float kRadianToDegree = 1.0f / kDegreeToRadian;
using vec4 = vcl::Vec4f;
using vec3 = vcl::Vec3Df;
using quat = vcl::Quaternion1f;
class matrix {
 public:
  static matrix scale(const float scale[3]);
  static matrix rotation(const float quat[4]);
  static matrix translation(const float translation[3]);
  static matrix identity();
  static matrix transpose(const matrix& m);
  matrix();
  matrix(const vec4& column0, const vec4& column1, const vec4& column2, const vec4& column3); // columns
  matrix(const float m00, const float m01, const float m02, const float m03,
         const float m10, const float m11, const float m12, const float m13,
         const float m20, const float m21, const float m22, const float m23,
         const float m30, const float m31, const float m32, const float m33);
  matrix operator *(const matrix& m);
  matrix operator *=(const matrix& m);
  bool operator == (const matrix& m) const;
  vec4 m0, m1, m2, m3; // columns
};
vec4 __vectorcall append_w(const vec3& m, const float w);
vec4 __vectorcall mul(const matrix& m, const vec4& v);
matrix __vectorcall transpose(const matrix& m);
matrix __vectorcall lookat_lh(const vec3& from, const vec3& to, const vec3& up_world = vec3(0.0f, 1.0f, 0.0f));
matrix __vectorcall perspective_projection_lh(const float fov_vertical_radian, const float aspect_ratio, const float z_near, const float z_far);
vec3 __vectorcall perspective_division(const vec4& v);
quat normalize(const quat& q);
void __vectorcall to_array(const vec4& src, float dst[4]);
void __vectorcall to_array(const vec3& src, float dst[3]);
void __vectorcall to_array_row_major(const matrix& src, float dst[16]);
void __vectorcall to_array_column_major(const matrix& src, float dst[16]);
void __vectorcall set_matrix_with_row_major_array(const float src[16], matrix* dst);
void __vectorcall set_matrix_with_column_major_array(const float src[16], matrix* dst);
}
#endif
