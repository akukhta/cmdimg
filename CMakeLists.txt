cmake_minimum_required(VERSION 3.15)
project(cmdimg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} 
	src/Common/main.cpp
	src/Common/Dimentions.hpp
	src/Common/ArgsParser.ixx
	src/Common/ArgsParser.cpp
	src/Image/NearestNeighboorCompressor.ixx
	src/Image/NearestNeighboorCompressor.cpp
    	src/Image/ImageParser.ixx
    	src/Image/ImageParser.cpp
	src/Image/RGB.ixx
	src/Image/RGB.cpp
	src/GUI/fxtprinter.ixx
	src/GUI/fxtprinter.cpp
)

target_include_directories(cmdimg PRIVATE ftxuilib/include)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM "Win32")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CONFIGURATION "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CONFIGURATION "Release")
else()
    message(FATAL_ERROR "Unknown or unsupported build configuration")
endif()

set(LIBRARY_NAMES ftxui-component.lib ftxui-dom.lib ftxui-screen.lib)
set(LIBRARY_PATHS "")

foreach(LIBRARY_NAME ${LIBRARY_NAMES})
    message("Search for: ${CMAKE_SOURCE_DIR}/ftxuilib/Windows/${PLATFORM}/${CONFIGURATION}/${LIBRARY_NAME}")
    find_library(LIB_${LIBRARY_NAME}_LIBRARY
        NAMES ${LIBRARY_NAME}
        PATHS "${CMAKE_SOURCE_DIR}/ftxuilib/Windows/${PLATFORM}/${CONFIGURATION}/"
    )
    
    if(NOT LIB_${LIBRARY_NAME}_LIBRARY)
        message(FATAL_ERROR "${LIBRARY_NAME} library not found")
    endif()

    list(APPEND LIBRARY_PATHS ${LIB_${LIBRARY_NAME}_LIBRARY})
endforeach()

set( OpenCV_DIR )
if( NOT CMAKE_CL_64 )
  set( OpenCV_DIR "C:/vcpkg/installed/x86-windows/share/opencv" )
else()
  set( OpenCV_DIR "C:/vcpkg/installed/x64-windows/share/opencv" )
endif()

find_package(OpenCV REQUIRED)

if( OpenCV_FOUND )
  include_directories( ${OpenCV_INCLUDE_DIRS} )
  link_directories( ${OpenCV_LIB_DIR} )
  target_link_libraries(cmdimg ${OpenCV_LIBS} )
endif()

target_link_libraries(cmdimg ${LIBRARY_PATHS})