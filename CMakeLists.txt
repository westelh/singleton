cmake_minimum_required(VERSION 2.8)
project(singleton CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
option(BUILD_TESTS OFF)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

# On windows, remove lib prefix
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Compiler options
if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -march=native")
    set(CMAKE_CXX_RELEASE_FLAGS "-O2")
    set(CMAKE_CXX_DEBUG_FLAGS "-g3 -fsanitize=leak -fsanitise=address")
endif()

include_directories(include)
add_library(singleton STATIC src/singleton_finalizer.cpp)

if(BUILD_TESTS)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(singletonTest src/test/singletonTest.cpp)
    target_link_libraries(singletonTest singleton ${GTEST_BOTH_LIBRARIES})
    add_test(singletonTest singletonTest)
endif()
