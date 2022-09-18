#include "gfxminimath/gfxminimath.h"
#include <doctest/doctest.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-identifier"
TEST_CASE("vector") {
  using namespace gfxminimath;
  vec4 v(0.0f, 1.0f, 1.0f, 1.0f);
  CHECK_UNARY(true);
}
#pragma clang diagnostic pop
