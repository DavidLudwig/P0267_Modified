cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(rulers_2d main.cpp)

target_link_libraries(rulers_2d io2d)

install(TARGETS rulers_2d
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
