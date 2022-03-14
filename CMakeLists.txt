# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project ("HaedsProtoStruct")
message ("PROJECT_NAME (From Top-Level): " ${PROJECT_NAME})

# Set C++17 for all projects and disable non-standard extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest CONFIG REQUIRED)

# Include sub-projects.
add_subdirectory ("HaedsCommon")
add_subdirectory ("HaedsConfig")
add_subdirectory ("UnitTest")