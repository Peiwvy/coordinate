#include "coordinate.h"

#include <cmath>
#include <gtest/gtest.h>

TEST(WSG84_to_UTM, test1) {
  Coordinate c(355000, 2700000, 0);
  double     x = 0.0;
  double     y = 0.0;
  double     z = 0.0;
  c.WGS84_to_UTM(24.3358698, 109.3664775, x, y);
  std::cout << x << " " << y << std::endl;
  ASSERT_NEAR(x, 334271.7973813771, 1e-3);
  ASSERT_NEAR(y, 2692386.5379031631, 1e-3);

  c.utm_offset(x, y, z);
  ASSERT_NEAR(x, -20728.2026186229, 1e-3);
  ASSERT_NEAR(y, -7613.4620968369, 1e-3);
}
