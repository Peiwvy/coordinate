#include "coordinate.h"

Coordinate::Coordinate(const YAML::Node& config_node) {
  // output neeeded be colorzierd
  std::cout << " Coordinate Config start" << std::endl;

  if (config_node.size() == 3) {
    utm_origin_x_ = config_node[0].as<double>();
    utm_origin_y_ = config_node[1].as<double>();
    utm_origin_z_ = config_node[2].as<double>();

    std::cout << "utm offset:[" << std::fixed << utm_origin_x_ << ", " << utm_origin_y_ << ", " << utm_origin_z_ << "] " << std::endl;
  } else if (config_node.size() == 5) {
    utm_origin_x_ = config_node[0].as<double>();
    utm_origin_y_ = config_node[1].as<double>();
    utm_origin_z_ = config_node[2].as<double>();
    zone_         = config_node[3].as<int>();
    northp_       = config_node[4].as<bool>();

    std::cout << "utm offset:[" << std::fixed << utm_origin_x_ << ", " << utm_origin_y_ << ", " << utm_origin_z_ << "] " << std::endl;
    std::cout << "zone: " << zone_ << " northp: " << northp_ << std::endl;
  } else
    std::cout << " Coordinate config error" << std::endl;
}

Coordinate::Coordinate(double utm_origin_x, double utm_origin_y, double utm_origin_z) {
  utm_origin_x_ = utm_origin_x;
  utm_origin_y_ = utm_origin_y;
  utm_origin_z_ = utm_origin_z;
  std::cout << "'Set utm origin point at: [" << utm_origin_x_ << ", " << utm_origin_y_ << ", " << utm_origin_z_ << "] " << std::endl;
}

void Coordinate::WGS84_to_UTM(const double lat, const double lon, double& x, double& y) {
  utm_converter_.Forward(lat, lon, zone_, northp_, x, y);
}

void Coordinate::UTM_to_WGS84(const double x, const double y, double& lat, double& lon) {
  utm_converter_.Reverse(zone_, northp_, x, y, lat, lon);
}

void Coordinate::utm_offset(double& x, double& y, double& z) {
  x -= utm_origin_x_;
  y -= utm_origin_y_;
  z -= utm_origin_z_;
}

void Coordinate::utm_offset_inverse(double& x, double& y, double& z) {
  x += utm_origin_x_;
  y += utm_origin_y_;
  z += utm_origin_z_;
}

void Coordinate::get_zone_northp(int& zone, bool& northp) {
  zone   = zone_;
  northp = northp_;
}