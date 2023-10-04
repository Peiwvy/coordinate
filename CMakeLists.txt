cmake_minimum_required(VERSION 3.10)
project(coordinate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(yaml-cpp REQUIRED)
find_package(GeographicLib REQUIRED)
find_package(Eigen3 REQUIRED)

add_library(coordinate SHARED coordinate.cc)
add_library(common::coordinate ALIAS coordinate)
target_include_directories(
  coordinate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${YAML_CPP_INCLUDEDIR}
                    ${Eigen3_INCLUDE_DIRS}
  )
target_link_libraries(
  coordinate PUBLIC ${YAML_CPP_LIBRARIES} ${GeographicLib_LIBRARIES}
  )

option(BUILD_TEST "Build TEST" OFF)
option(BUILD_TEST_ROS_ENV "BUILD TEST ROS" OFF)
if(BUILD_TEST)
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
  link_libraries(${GTEST_BOTH_LIBRARIES} coordinate)

  add_executable(coordinate_test coordinate_test.cc)

  if(BUILD_TEST_ROS_ENV)
    find_package(catkin REQUIRED COMPONENTS roscpp geographic_msgs geodesy)
    add_executable(coordinate_ros_test coordinate_ros_test.cc)
    target_include_directories(
      coordinate_ros_test PRIVATE ${catkin_INCLUDE_DIRS}
      )
    target_link_libraries(coordinate_ros_test ${catkin_LIBRARIES})
  endif()
endif()
