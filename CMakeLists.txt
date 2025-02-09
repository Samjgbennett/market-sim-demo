# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProgram)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(
    "${PROJECT_SOURCE_DIR}/src/file_handling.h.in"
    "${PROJECT_SOURCE_DIR}/src/file_handling.h"
    @ONLY
)

set(SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp 
              ${CMAKE_SOURCE_DIR}/src/Asset.cpp 
              ${CMAKE_SOURCE_DIR}/src/AssetHistory.cpp 
              ${CMAKE_SOURCE_DIR}/src/HistoryObserver.cpp
              ${CMAKE_SOURCE_DIR}/src/Market.cpp
              ${CMAKE_SOURCE_DIR}/src/Portfolio.cpp
              ${CMAKE_SOURCE_DIR}/src/TimeSeries.cpp
              ${CMAKE_SOURCE_DIR}/src/Trader.cpp
              ${CMAKE_SOURCE_DIR}/src/Util.cpp)
               
add_executable(my_program ${SRC_FILES})
target_include_directories(my_program PRIVATE ${CMAKE_SOURCE_DIR}/src)

####################### TESTING STUFF STARTS HERE ###########################################################

enable_testing()
add_subdirectory(tests)