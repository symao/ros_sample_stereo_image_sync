cmake_minimum_required(VERSION 2.8.3)
project(sample_nodelet)

find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  rospy
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES ${PROJECT_NAME}
 CATKIN_DEPENDS nodelet roscpp rospy
 # DEPENDS system_lib
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} src/sample_nodelet.cpp)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
