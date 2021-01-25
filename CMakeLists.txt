cmake_minimum_required(VERSION 3.17)
project(dpg_layout VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADER_FILES include/box_helper.h include/constrainable.h include/geometry.h include/spacers.h include/strength.h include/utils.h include/sequence_helper.h include/common.h include/constraint_helper.h src/constraint_helper.cpp)

add_executable(dpg_layout ${HEADER_FILES} src/box_helper.cpp src/main.cpp src/spacers.cpp src/strength.cpp )

target_include_directories(dpg_layout PRIVATE include deps/kiwi)
