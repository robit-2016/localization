cmake_minimum_required(VERSION 2.8.3)
project(localization)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy message_generation std_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES Samples.msg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker localization_generate_messages_cpp)

add_executable(localizer src/main.cpp  src/localizer.cpp)
target_link_libraries(localizer ${catkin_LIBRARIES})
add_dependencies(localizer localization_generate_messages_cpp)

