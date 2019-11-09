cmake_minimum_required(VERSION 2.8.3)
project(bebop_posmen)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  roscpp
  rospy
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(AbgPosmen_bebop src/AbgPosmen_bebop.cpp)
target_link_libraries(AbgPosmen_bebop ${catkin_LIBRARIES} )
add_dependencies(AbgPosmen_bebop bebop_posmen_generate_messages_cpp)
