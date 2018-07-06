cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(measurement_guides_2d main.cpp)

target_link_libraries(measurement_guides_2d io2d)

install(TARGETS measurement_guides_2d
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
