cmake_minimum_required(VERSION 3.20)
project(exr2hdr VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include(vendor/openexr/cmake/OpenEXRConfig.h)

include_directories(vendor/openexr/src/lib)

add_subdirectory(vendor/openexr)

file(GLOB_RECURSE PROJECT_SOURCE CONFIGURE_DEPENDENT ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

target_link_directories(${PROJECT_NAME} PRIVATE OpenEXR)