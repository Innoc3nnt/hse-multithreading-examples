set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_executable(buffered_channel_test test.cpp)
target_link_libraries(buffered_channel_test Threads::Threads GTest::gtest GTest::gtest_main)

add_executable(buffered_channel_benchmark benchmark.cpp)
target_link_libraries(buffered_channel_benchmark Threads::Threads benchmark::benchmark)