cmake_minimum_required(VERSION 3.22)

message(${CMAKE_HOST_SYSTEM_NAME})
#message(${CMAKE_HOST_SYSTEM_PROCESSOR})

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    message("this is Linux")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Android")
    message("this is Android")
endif()
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    message("this is aarch64 cpu")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    message("this is x86_64 cpu")
endif()

project(nesp_logger)

set(CMAKE_CXX_STANDARD 17)

file(GLOB header_files src/main/include/*.h)
file(GLOB source_files src/main/include/*.h src/main/cpp/*.cpp)
#file(GLOB test_source_files src/test/include/*.h src/test/cpp/*.cpp)

add_library(
        nesp_logger
        SHARED
        ${header_files}
        ${source_files}
)

target_link_libraries(
        nesp_logger
        -lz
)

#add_executable(test ${test_source_files})

#target_link_libraries(
#        test
#        nesp_logger
#)

# Testing

add_executable(benchmark src/test/cpp/benchmark.cpp)

target_link_libraries(
        benchmark
        nesp_logger
)

add_executable(gzip-test src/test/cpp/gzip_test.cpp)

target_link_libraries(
        gzip-test
        nesp_logger
)
