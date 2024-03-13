cmake_minimum_required(VERSION 3.0)

project(Oop-3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_subdirectory(lib/googletest)
INCLUDE_DIRECTORIES(gtest lib/googletest/googletest/include)

add_executable(CarControl 1-2/CarControl.cpp 1-2/Car.cpp)
add_executable(CarTests 1-2/Tests/CarTests.cpp 1-2/Car.cpp)

target_link_libraries(CarTests gtest)


