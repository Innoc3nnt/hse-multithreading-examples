set(CMAKE_CXX_STANDARD 17)

add_executable(producer main.cpp mpsc_queue.cpp shared_memory.cpp)
target_compile_definitions(producer PRIVATE PRODUCER)
target_link_libraries(producer pthread rt)

add_executable(consumer main.cpp mpsc_queue.cpp shared_memory.cpp)
target_compile_definitions(consumer PRIVATE CONSUMER)
target_link_libraries(consumer pthread rt)