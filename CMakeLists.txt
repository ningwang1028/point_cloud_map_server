cmake_minimum_required(VERSION 2.8.3)
project(point_cloud_map_server)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -o3")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

find_package(PCL REQUIRED)

catkin_package(
)

include_directories(
  src
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(map_loader
  src/map_loader.cpp
)

add_executable(map_saver
  src/map_saver.cpp
)

target_link_libraries(map_loader
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

target_link_libraries(map_saver
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

install(TARGETS map_loader map_saver
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
