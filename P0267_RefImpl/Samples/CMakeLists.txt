cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

if(EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/emscripten_template_page.html" )
endif()

# add_subdirectory(DrawCPP)
add_subdirectory(RocksInSpace)
# add_subdirectory(SVG)
add_subdirectory(Life)
# add_subdirectory(CPULoad)
# add_subdirectory(Sprites)
add_subdirectory(ColorFill)
add_subdirectory(Rulers2D)
