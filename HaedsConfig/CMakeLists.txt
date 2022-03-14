# CMakeList.txt : CMake project for HaedsConfig library
#
cmake_minimum_required (VERSION 3.19)

project ("HaedsConfig")

message ("PROJECT_NAME (From HaedsConfig): " ${PROJECT_NAME})
message ("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

add_library (${PROJECT_NAME} STATIC "src/IniParser.cpp" "include/IniParser.h" "include/INIReader.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)