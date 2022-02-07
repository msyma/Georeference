cmake_minimum_required(VERSION 3.19)
project(georeference)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

# Tests
add_executable(Google_Tests_run

        test/matrixTest.cpp
        src/matrix.cpp src/matrix.h

        test/georeferenceTest.cpp
        src/georeference.cpp src/georeference.h
        src/algebra.cpp src/algebra.h
        src/matrix.cpp src/matrix.h)

target_link_libraries(Google_Tests_run gtest gtest_main)
add_subdirectory(test/google_test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("-> Debug!")
    add_executable(georeference src/main.cpp
            src/matrix.cpp src/matrix.h
            src/algebra.cpp src/algebra.h
            src/georeference.cpp src/georeference.h src/config.h)
endif ()
