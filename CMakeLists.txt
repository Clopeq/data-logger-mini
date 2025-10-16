cmake_minimum_required(VERSION 3.28)

project(main)

include_directories(lib/ADC)
add_subdirectory(lib/ADC)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} lib/ADC)