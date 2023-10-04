#pragma once

#include <GeographicLib/UTMUPS.hpp>

#include <yaml-cpp/yaml.h>

#include <iostream>

class Coordinate {
  // [x_offset, y_offset, z_offset, zone, northp] <---> [lat, lon, alt]
 public:
  explicit Coordinate(const YAML::Node& config_node);
  Coordinate(double utm_origin_x, double utm_origin_y, double utm_origin_z);
  void WGS84_to_UTM(const double lat, const double lon, double& x,
                    double& y);  // geographic_coordinate
  void UTM_to_WGS84(const double x, const double y, double& lat, double& lon);
  void utm_offset(double& x, double& y, double& z);
  void utm_offset_inverse(double& x, double& y, double& z);
  void get_zone_northp(int& zone, bool& northp);

 private:
  static GeographicLib::UTMUPS utm_converter_;

  int    zone_;
  bool   northp_;
  double utm_origin_x_ = 0;
  double utm_origin_y_ = 0;
  double utm_origin_z_ = 0;
};
