#include "gfxminimath/gfxminimath.h"
namespace gfxminimath {
matrix::matrix() {}
matrix::matrix(const vec4& column0, const vec4& column1, const vec4& column2, const vec4& column3) : m0(column0), m1(column1), m2(column2), m3(column3) {}
matrix::matrix(const float m00, const float m01, const float m02, const float m03,
               const float m10, const float m11, const float m12, const float m13,
               const float m20, const float m21, const float m22, const float m23,
               const float m30, const float m31, const float m32, const float m33)
    : m0(m00, m10, m20, m30)
    , m1(m01, m11, m21, m31)
    , m2(m02, m12, m22, m32)
    , m3(m03, m13, m23, m33) {
}
vec4 append_w(const vec3& v, const float w) {
  vec4 v4(v);
  v4.insert(3, w);
  return v4;
}
vec4 mul(const matrix& m, const vec4& v) {
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
matrix transpose(const matrix& m) {
  float array[16];
  to_array(m.m0, &array[0]);
  to_array(m.m1, &array[4]);
  to_array(m.m2, &array[8]);
  to_array(m.m3, &array[12]);
  return matrix(vec4(array[0], array[4], array[8], array[12]),
                vec4(array[1], array[5], array[9], array[13]),
                vec4(array[2], array[6], array[10], array[14]),
                vec4(array[3], array[7], array[11], array[15]));
}
matrix lookat(const vec3& from, const vec3& to, const vec3& up_world) {
  // https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixlookatlh
  auto view  = normalize_vector(to - from);
  auto right = normalize_vector(cross_product(up_world, view));
  auto up    = cross_product(right, view);
  float array[12];
  to_array(right, &array[0]);
  to_array(up,    &array[4]);
  to_array(view,  &array[8]);
  array[ 3] = -dot_product(from, right);
  array[ 7] = -dot_product(from, up);
  array[11] = -dot_product(from, view);
  return matrix(vec4(array[0], array[4], array[8], 0.0f),
                vec4(array[1], array[5], array[9], 0.0f),
                vec4(array[2], array[6], array[10], 0.0f),
                vec4(array[3], array[7], array[11], 1.0f));
}
vec3 perspective_division(const vec4& v) {
  // https://shikihuiku.github.io/post/projection_matrix/
  vec4 w = permute4<3,3,3,3>(v);
  return vec3(v * approx_recipr(w));
}
void to_array(const vec4& src, float dst[4]) {
  src.store(dst);
}
void to_array(const vec3& src, float dst[3]) {
  src.store(dst);
}
void to_array_row_major(const matrix& src, float dst[16]) {
  const auto m = transpose(src);
  to_array_column_major(m, dst);
}
void to_array_column_major(const matrix& src, float dst[16]) {
  // hlsl default
  // https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-appendix-pre-pragma-pack-matrix
  src.m0.store(&dst[0]);
  src.m1.store(&dst[4]);
  src.m2.store(&dst[8]);
  src.m3.store(&dst[12]);
}
} // namespace gfxminimath
#include <doctest/doctest.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-identifier"
#pragma clang diagnostic ignored "-Wdouble-promotion"
TEST_CASE("matrix * vector") {
  using namespace gfxminimath;
  matrix m(1.0f, 2.0f, 3.0f, 4.0f,
           4.0f, 3.0f, 2.0f, 1.0f,
           -1.0f, 1.0f, 2.0f, 3.0f,
           4.0f, 3.0f, -2.0f, 1.0f
           );
  vec4 v(1.0f, -2.0f, 3.0f, -4.0f);
  auto result = mul(m, v);
  float result_array[4];
  to_array(result, result_array);
  CHECK_EQ(result_array[0], doctest::Approx(-26.0));
  CHECK_EQ(result_array[1], doctest::Approx(-13.0));
  CHECK_EQ(result_array[2], doctest::Approx(13.0));
  CHECK_EQ(result_array[3], doctest::Approx(7.0));
}
TEST_CASE("perspective division") {
  using namespace gfxminimath;
  vec4 v(1.0f, -2.0f, 3.0f, -4.0f);
  auto w = perspective_division(v);
  float result_array[3];
  to_array(w, result_array);
  CHECK_EQ(result_array[0], doctest::Approx(-0.25).epsilon(0.001));
  CHECK_EQ(result_array[1], doctest::Approx(0.5).epsilon(0.001));
  CHECK_EQ(result_array[2], doctest::Approx(-0.75).epsilon(0.001));
}
TEST_CASE("lookat") {
  using namespace gfxminimath;
  vec3 from(1.0f, 2.0f, 3.0f);
  vec3 to(-1.0f, -3.0f, 5.0f);
  auto view_mat = lookat(from, to);
  float result_array[16];
  to_array_row_major(view_mat, result_array);
  auto view = normalize_vector(to - from);
  vec3 up_world(0.0f, 1.0f, 0.0f);
  auto right = normalize_vector(cross_product(up_world, view));
  auto up = cross_product(right, view);
  auto tx = -dot_product(right, from);
  auto ty = -dot_product(up,    from);
  auto tz = -dot_product(view,  from);
  float view_array[3];
  float up_array[3];
  float right_array[3];
  to_array(right, right_array);
  to_array(up, up_array);
  to_array(view, view_array);
  CHECK_EQ(result_array[0], doctest::Approx(right_array[0]).epsilon(0.001));
  CHECK_EQ(result_array[1], doctest::Approx(right_array[1]).epsilon(0.001));
  CHECK_EQ(result_array[2], doctest::Approx(right_array[2]).epsilon(0.001));
  CHECK_EQ(result_array[3], doctest::Approx(tx).epsilon(0.001));
  CHECK_EQ(result_array[4], doctest::Approx(up_array[0]).epsilon(0.001));
  CHECK_EQ(result_array[5], doctest::Approx(up_array[1]).epsilon(0.001));
  CHECK_EQ(result_array[6], doctest::Approx(up_array[2]).epsilon(0.001));
  CHECK_EQ(result_array[7], doctest::Approx(ty).epsilon(0.001));
  CHECK_EQ(result_array[8], doctest::Approx(view_array[0]).epsilon(0.001));
  CHECK_EQ(result_array[9], doctest::Approx(view_array[1]).epsilon(0.001));
  CHECK_EQ(result_array[10], doctest::Approx(view_array[2]).epsilon(0.001));
  CHECK_EQ(result_array[11], doctest::Approx(tz).epsilon(0.001));
  CHECK_EQ(result_array[12], doctest::Approx(0).epsilon(0.001));
  CHECK_EQ(result_array[13], doctest::Approx(0).epsilon(0.001));
  CHECK_EQ(result_array[14], doctest::Approx(0).epsilon(0.001));
  CHECK_EQ(result_array[15], doctest::Approx(1).epsilon(0.001));
}
#pragma clang diagnostic pop
