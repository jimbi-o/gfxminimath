#include "gfxminimath/gfxminimath.h"
#include <doctest/doctest.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-identifier"
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
TEST_CASE("perspective_division") {
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
#pragma clang diagnostic pop
