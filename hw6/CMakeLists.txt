cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(tests Tests.cpp ThreadPool.cpp ProcessPool.cpp)
target_link_libraries(tests GTest::gtest GTest::gtest_main)