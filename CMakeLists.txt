cmake_minimum_required(VERSION 3.5)
project(singleton CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

# On windows, remove lib prefix
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Compiler options
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -fsanitise=address -fsanitise=leak")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(include)
add_library(singleton STATIC src/singleton_finalizer.cpp)
