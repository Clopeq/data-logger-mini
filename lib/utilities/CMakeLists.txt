
set(LIB_NAME utilities)

# Create library target
add_library(${LIB_NAME})

# Collct sources
file(GLOB SRC_FILES src/*.cpp)
target_sources(${LIB_NAME} PRIVATE ${SRC_FILES}) # Add them to the target

# Add include directory for this library
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)