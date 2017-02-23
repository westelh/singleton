cmake_minimum_required(VERSION 3.5)
project(logger CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_COLOR_MAKEFILE ON)

# On windows, remove lib prefix
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Compiler options
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -fsanitise=address -fsanitise=leak")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

include_directories(include)
add_library(singleton STATIC src/singleton_finalizer.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set_target_properties(singleton PROPERTIES
    PUBLIC_HEADER include/singleton/singleton.h
    PUBLIC_HEADER include/singleton/singleton_finalizer.h
)

install(TARGETS singleton
    EXPORT singleton-export
    ARCHIVE         DESTINATION lib/static
    LIBRARY         DESTINATION lib
    INCLUDES        DESTINATION include
    PUBLIC_HEADER   DESTINATION include/singleton
)

install(EXPORT singleton-export
    FILE singleton-config.cmake
    DESTINATION share/cmake/singleton/
    EXPORT_LINK_INTERFACE_LIBRARIES
)
