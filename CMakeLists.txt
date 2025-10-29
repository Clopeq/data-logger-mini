# Workflow - root CMake:
# 1. cmake_minimum_required(VERSION 3.25)
# 2. project(PROJECT NAME) - this will be the name of the executable
# 3. include CMakeLists from subdirectories
# 4. include source files
# 5. crete executable
# 6. include .h files
# 7. link libraries

# Workflow - libraries:
# 1. crate a target
# 2. collect source files
# 3. add sources to the target
# 4. include .h files

# Workflow - library collective directory:
# 1. add CMakeLists.txt form each library 

cmake_minimum_required(VERSION 3.25)
project(main)

# Add CMakeLists.txt from /lib subdirectory
add_subdirectory(lib)

# Gather main sources from /src folder
file(GLOB SRC_FILES src/*.cpp) # GLOB - recursivly, SRC_FILES - a name, can be whatever, src/*.cpp - all .cpp files from /src folder

# Create the main executable.
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

# Include the top-level directory containing .h files
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ADC WPI utilities json)# json sensors) # list all of the libraries