
set(LIB_NAME ADC)

# Create library target
add_library(${LIB_NAME})

# Collct sources
file(GLOB SRC_FILES src/*.cpp Config/src/*.cpp)

# Add them to the target
target_sources(${LIB_NAME} PRIVATE ${SRC_FILES})

# Add include directory for this library
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/Config/lib)

target_link_libraries(${LIB_NAME} PUBLIC json)