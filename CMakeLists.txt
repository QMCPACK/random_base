cmake_minimum_required( VERSION 3.22 )

project( random_base CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Set a default build type if none was specified
# https://blog.kitware.com/cmake-and-the-default-build-type/
set (default_build_type "Release")
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
	set (default_build_type "Debug")
endif ()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message (STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set (CMAKE_BUILD_TYPE "${default_build_type}" CACHE
       STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
else ()
  message (STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
endif ()

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.0)
FetchContent_MakeAvailable(
	googletest
        googlebenchmark)

add_executable(g_benchmark src/benchmark.cpp src/StdRandom.cpp src/FakeRandom.cpp)
#target_include_directories(g_benchmark src)
target_link_libraries(g_benchmark benchmark::benchmark)

