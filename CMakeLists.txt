cmake_minimum_required(VERSION 3.0)

project(Oop-3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")
##set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

add_subdirectory(lib/googletest)
INCLUDE_DIRECTORIES(gtest lib/googletest/googletest/include)

add_executable(CarControl 1-2/CarControl.cpp 1-2/Car.cpp)
add_executable(CarTests 1-2/Tests/CarTests.cpp 1-2/Car.cpp)

add_executable(CalculatorFast 2-f/CalcControl.cpp 2-f/Calculator.cpp)
add_executable(CalculatorFastTests 2-f/CalcTests/CalculatorTests.cpp 2-f/Calculator.cpp)

add_executable(CalculatorTests 2/CalcTests/CalculatorTests.cpp 2/Calculator.cpp)
add_executable(Calculator 2/CalcControl.cpp 2/Calculator.cpp)



target_link_libraries(CarTests gtest)
target_link_libraries(CalculatorFastTests gtest_main)
target_link_libraries(CalculatorTests gtest_main)


