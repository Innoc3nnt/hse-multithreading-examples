set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_executable(tests test.cpp)
target_link_libraries(tests GTest::gtest GTest::gtest_main)

add_executable(bench Benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)