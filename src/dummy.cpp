#include "gfxminimath/gfxminimath.h"
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
  float result_array[4];
  to_array(w, result_array);
  CHECK_EQ(result_array[0], doctest::Approx(-0.25).epsilon(0.001));
  CHECK_EQ(result_array[1], doctest::Approx(0.5).epsilon(0.001));
  CHECK_EQ(result_array[2], doctest::Approx(-0.75).epsilon(0.001));
  CHECK_EQ(result_array[3], doctest::Approx(1.0).epsilon(0.001));
}
TEST_CASE("lookat") {
  using namespace gfxminimath;
  vec3 from(1.0f, 2.0f, 3.0f);
  vec3 to(-1.0f, -3.0f, 5.0f);
  auto view_mat = lookat(from, to);
  float result_array[16];
  to_array_row_major(view_mat, result_array);
  auto view = normalize_vector(from - to);
  vec3 up_world(0.0f, 1.0f, 0.0f);
  auto right = -normalize_vector(cross_product(view, up_world));
  auto up = cross_product(view, right);
  auto tx = -dot_product(from, right);
  auto ty = -dot_product(from, up);
  auto tz = -dot_product(from, view);
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
