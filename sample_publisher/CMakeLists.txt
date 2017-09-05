cmake_minimum_required(VERSION 2.8.3)
project(sample_publisher)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  image_transport
  cv_bridge
  nodelet
)

# find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES ${PROJECT_NAME}
 CATKIN_DEPENDS roscpp rospy std_msgs nodelet cv_bridge image_transport
 # DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} src/sample_publisher_nodelet.cpp)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} cv_bridge image_transport)

add_executable(${PROJECT_NAME}_node src/sample_publisher_node.cpp)

target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
