#include "gfxminimath/gfxminimath.h"
#include <doctest/doctest.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-identifier"
TEST_CASE("vector * matrix") {
  using namespace gfxminimath;
  matrix m(1.0f, 2.0f, 3.0f, 4.0f,
           4.0f, 3.0f, 2.0f, 1.0f,
           -1.0f, 1.0f, 2.0f, 3.0f,
           4.0f, 3.0f, -2.0f, 1.0f
           );
  vec4 v(1.0f, -2.0f, 3.0f, -4.0f);
  auto result = mul(v, m);
  float result_array[4];
  GetValue(result, result_array);
#pragma clang diagnostic ignored "-Wdouble-promotion"
  CHECK_EQ(result_array[0], doctest::Approx(-26.0f));
  CHECK_EQ(result_array[1], doctest::Approx(-13.0f));
  CHECK_EQ(result_array[2], doctest::Approx(13.0f));
  CHECK_EQ(result_array[3], doctest::Approx(7.0f));
}
#pragma clang diagnostic pop
