
set(LIB_NAME json)

# Create library target
add_library(${LIB_NAME} INTERFACE)

# Add include directory for this library
target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)