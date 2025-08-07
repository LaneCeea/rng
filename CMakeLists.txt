cmake_minimum_required(VERSION 3.16)

project(rng VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

configure_file(
    "${CMAKE_SOURCE_DIR}/config.h.in"  # Input template
    "${CMAKE_BINARY_DIR}/config.h"     # Output file
    @ONLY  # Only substitute @VAR@ not ${VAR}
)

############################################################
# PRNG
############################################################

set(PRNG_SOURCES
    src/prng/mt19937.c
    src/prng/pcg32.c
    src/prng/standard.c
    src/prng/xoshiro128plusplus.c
)

set(PRNG_HEADERS
    src/prng/mt19937.h
    src/prng/pcg32.h
    src/prng/standard.h
    src/prng/xoshiro128plusplus.h
    src/prng.hpp
)

add_library(prng STATIC ${PRNG_SOURCES})

# This allows using #include "prng.hpp" etc.
target_include_directories(prng 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set_target_properties(prng PROPERTIES
    OUTPUT_NAME prng
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

############################################################
# DIST
############################################################

set(DIST_SOURCES
    src/dist/continuous.c
)

set(DIST_HEADERS
    src/dist/continuous.h
    src/dist.hpp
)

add_library(dist STATIC ${DIST_SOURCES})

# This allows using #include "dist.hpp" etc.
target_include_directories(dist 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set_target_properties(dist PROPERTIES
    OUTPUT_NAME dist
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

############################################################
# TESTS
############################################################

add_executable(prng_speed
    tests/prng_speed.cpp
    tests/timer.hpp
)
target_link_libraries(prng_speed PRIVATE prng)
set_target_properties(prng_speed PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_executable(dist_speed
    tests/dist_speed.cpp
    tests/timer.hpp
)
target_link_libraries(dist_speed PRIVATE prng dist)
set_target_properties(dist_speed PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_executable(dist_gen 
    tests/dist_gen.cpp
    tests/timer.hpp
)
target_include_directories(dist_gen PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(dist_gen PRIVATE prng dist)
set_target_properties(dist_gen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_UPPER)
message(STATUS "C flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${BUILD_TYPE_UPPER}}")
message(STATUS "C++ flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${BUILD_TYPE_UPPER}}")