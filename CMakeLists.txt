
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF("" STREQUAL "${CMAKE_BUILD_TYPE}")
  SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
  MESSAGE(STATUS "CMAKE_BUILD_TYPE set to '" ${CMAKE_BUILD_TYPE} "'")
ENDIF()

PROJECT(KINECTJUGGLER)

# where to find project-specific cmake modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# globally visible functions/modules
INCLUDE(BuildFunctions)

# disallow in-source build
IF("${KINEXTJUGGLER_SOURCE_DIR}" STREQUAL "${KINECTJUGGLER_BINARY_DIR}")
  MESSAGE(FATAL_ERROR
    "Kinect-Juggler requires an out-of-source build.\n"
    "Please create a separate build directory and run CMake there."
    "Consult README.build for command-line examples.")
ENDIF()

ADD_SUBDIRECTORY(src)
