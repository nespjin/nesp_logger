cmake_minimum_required(VERSION 3.24)
project(nesp_logger)

set(CMAKE_CXX_STANDARD 17)

file(GLOB header_files src/main/include/*.h)
file(GLOB source_files src/main/include/*.h src/main/cpp/*.cpp)
file(GLOB test_source_files src/test/include/*.h src/test/cpp/*.cpp)

add_library(
        nesp_logger
        SHARED
        ${header_files}
        ${source_files}
)

add_executable(test ${test_source_files})

target_link_libraries(
        test
        nesp_logger
)
