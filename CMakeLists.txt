cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
project(SpMM LANGUAGES C CXX)

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_SOURCE_DIR}/utils")

aux_source_directory (. SOURCES)
aux_source_directory (src SOURCES)
aux_source_directory (include SOURCES)
aux_source_directory (utils SOURCES)
add_library(SpMM STATIC ${SOURCES})

# add_test()
enable_testing()
add_subdirectory(tests)

include("etc/tests.cmake")