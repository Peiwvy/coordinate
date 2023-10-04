#include "coordinate.h"

#include <geodesy/utm.h>
#include <geographic_msgs/GeoPointStamped.h>

#include <cmath>
#include <gtest/gtest.h>

TEST(COMPARE_WITH_ROS, test1) {
  struct LatLng {
    double latitude;
    double longitude;
    double altitude;
  };

  std::vector<LatLng> testPoints = {{24.3358698, 109.3664775, 27}};

  double latitude  = 24.3358698;
  double longitude = 109.3664775;
  double altitude  = 27;

  for (const auto& point : testPoints) {
    double x = 0.0;
    double y = 0.0;

    Coordinate c(355000, 2700000, 0);
    c.WGS84_to_UTM(point.latitude, point.longitude, x, y);

    geographic_msgs::GeoPointStampedPtr gps_msg(new geographic_msgs::GeoPointStamped());
    gps_msg->position.latitude  = point.latitude;
    gps_msg->position.longitude = point.longitude;
    gps_msg->position.altitude  = point.altitude;

    geodesy::UTMPoint utm_point;
    geodesy::fromMsg(gps_msg->position, utm_point);
    std::cout << " utm_point:" << utm_point.band << " " << utm_point.zone << std::endl;

    geographic_msgs::GeoPoint geo_point = geodesy::toMsg(utm_point);

    ASSERT_NEAR(utm_point.easting, x, 1e-3);
    ASSERT_NEAR(utm_point.northing, y, 1e-3);
    ASSERT_NEAR(geo_point.latitude, point.latitude, 1e-3);
    ASSERT_NEAR(geo_point.longitude, point.longitude, 1e-3);
  }
}
