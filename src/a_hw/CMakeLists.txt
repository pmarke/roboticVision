cmake_minimum_required(VERSION 2.8.3)
project(a_hw)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(OpenCV REQUIRED)

include(FindPortaudio.txt)
# find_package(PortAudio)


# message("Port Audio Found: " ${PORTAUDIO_FOUND})



## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()



## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES a_hw
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)



#####################################
#            Definitions
#####################################
add_definitions(-DDEBUG=TRUE)



###########
## Build ##
###########

# get_filename_component(PARENT_DIR ${PROJECT_BINARY_DIR} DIRECTORY)

# find_library(PORTAUDIO_LIBRARY 
# 	NAMES
# 		portaudio
# 	PATHS
# 		${PARENT_DIR}/portaudio)

# find_path(PORTAUDIO_INCLUDE_DIR
# 	NAMES
# 		portaudio.h
# 	PATHS
# 		${CMAKE_SOURCE_DIR}/portaudio/include)

# message("PORTAUDIO_LIBRARY: " ${PORTAUDIO_LIBRARY})
# message("PORTAUDIO_INCLUDE_DIR: " ${PORTAUDIO_INCLUDE_DIR})
# message("Path: " ${CMAKE_SOURCE_DIR}/portaudio/include )

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PORTAUDIO_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/portaudio/qa/loopback/src
  include
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/a_hw.cpp
# )

set(WRITE_WAVE_PATH ${CMAKE_SOURCE_DIR}/portaudio/qa/loopback/src)

add_library(libaudioRecorder include/audioRecorder.h src/audioRecorder.cpp ${WRITE_WAVE_PATH}/write_wav.h ${WRITE_WAVE_PATH}/write_wav.c )

target_link_libraries(libaudioRecorder ${PORTAUDIO_LIBRARIES})





add_library(libscreenShot include/screenShot.h src/screenShot.cpp)

target_link_libraries(libscreenShot X11 Xrandr)

add_executable(main_node src/main.cpp )

target_link_libraries(main_node ${OpenCV_LIBRARIES} libscreenShot libaudioRecorder)



#############
## Testing ##
#############

## Add gtest based cpp test target and link PORTAUDIO_LIBRARIESlibraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_a_hw.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
