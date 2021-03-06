cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(cpuload)

set(CPULOAD_SRC
    main.cpp
    data_source.cpp
    data_source.h
    profiler.h
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    list(APPEND CPULOAD_SRC profiler_mach.cpp)
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    list(APPEND CPULOAD_SRC profiler_nt.cpp)
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    list(APPEND CPULOAD_SRC profiler_linux.cpp)
else()
    message( "CPULoad doesn't have a profiler for this platform, thus skipping." )
    return()
endif()

add_executable(cpuload ${CPULOAD_SRC})
target_link_libraries(cpuload io2d)

if( DEFINED IOS_PLATFORM )
    # iOS requires special packaging, so we have to treat this target separately
    set_target_properties(cpuload PROPERTIES MACOSX_BUNDLE YES)
    set_target_properties(cpuload PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/iOS/Info.plist")
    target_sources(cpuload PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard)
    target_sources(cpuload PRIVATE iOS/libcxx_tmp_stubs.cpp)
    set_target_properties(cpuload PROPERTIES RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard")
    set_target_properties(cpuload PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
endif()
