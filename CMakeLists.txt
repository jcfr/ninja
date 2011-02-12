
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(ninja)

OPTION(BUILD_TESTING "Enable testing" ON)

# Additional CXX/C Flags
SET(ADDITIONAL_C_FLAGS "" CACHE STRING "Additional C Flags")
SET(ADDITIONAL_CXX_FLAGS "" CACHE STRING "Additional CXX Flags")

SET(cflags "-Wno-deprecated")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT} ${cflags} ${ADDITIONAL_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} ${cflags} ${ADDITIONAL_CXX_FLAGS}")

CONFIGURE_FILE(
  src/browse.py
  ${CMAKE_CURRENT_BINARY_DIR}/src/browse.py COPY)

SET(ninja_lib_sources
  src/build.cc
  src/build_log.cc
  src/eval_env.cc
  src/graph.cc
  src/parsers.cc
  src/subprocess.cc
  src/util.cc
  src/ninja_jumble.cc
  )
ADD_LIBRARY(ninjaLib STATIC ${ninja_lib_sources})

ADD_EXECUTABLE(ninja src/ninja.cc)
TARGET_LINK_LIBRARIES(ninja ninjaLib)

IF(BUILD_TESTING)
  ENABLE_TESTING()
  INCLUDE(CTest)
  MARK_AS_ADVANCED(DART_TESTING_TIMEOUT)
  CONFIGURE_FILE(
    README
    ${CMAKE_CURRENT_BINARY_DIR}/README COPY)
  ADD_TEST(LongSlowBuild ninja -f ${CMAKE_CURRENT_SOURCE_DIR}/misc/long-slow-build.ninja all)
ENDIF()

