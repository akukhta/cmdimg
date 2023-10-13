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
    message("Search for: ${CMAKE_SOURCE_DIR}/libs/ftxuilib/Windows/${PLATFORM}/${CONFIGURATION}/${LIBRARY_NAME}")
    find_library(LIB_${LIBRARY_NAME}_LIBRARY
        NAMES ${LIBRARY_NAME}
        PATHS "${CMAKE_SOURCE_DIR}/libs/ftxuilib/Windows/${PLATFORM}/${CONFIGURATION}/"
    )
    
    if(NOT LIB_${LIBRARY_NAME}_LIBRARY)
        message(FATAL_ERROR "${LIBRARY_NAME} library not found")
    endif()

    list(APPEND LIBRARY_PATHS ${LIB_${LIBRARY_NAME}_LIBRARY})
endforeach()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPENCV_LIBRARY_NAMES opencv_core4d.lib opencv_imgcodecs4d.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OPENCV_LIBRARY_NAMES opencv_core4.lib opencv_imgcodecs4.lib)
else()
    message(FATAL_ERROR "Unknown or unsupported build configuration")
endif()

set(OPENCV_LIBRARY_PATHS "")

foreach(OPENCV_LIB_NAME ${OPENCV_LIBRARY_NAMES})
message("Search for: ${CMAKE_SOURCE_DIR}/libs/opencv/Windows/${PLATFORM}/${CONFIGURATION}/lib/${OPENCV_LIB_NAME}")
    find_library(LIB_${OPENCV_LIB_NAME}_LIBRARY
        NAMES ${OPENCV_LIB_NAME}
        PATHS "${CMAKE_SOURCE_DIR}/libs/opencv/Windows/${PLATFORM}/${CONFIGURATION}/lib"
    )
    
    if(NOT LIB_${OPENCV_LIB_NAME}_LIBRARY)
        message(FATAL_ERROR "${OPENCV_LIB_NAME} library not found")
    endif()

    list(APPEND LIBRARY_PATHS ${LIB_${OPENCV_LIB_NAME}_LIBRARY})
endforeach()

target_include_directories(cmdimg PRIVATE libs/ftxuilib/include libs/opencv/include)
target_link_libraries(cmdimg ${LIBRARY_PATHS} ${OPENCV_LIBRARY_PATHS})

add_custom_command(
    TARGET cmdimg
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/libs/opencv/Windows/Win32/${CONFIGURATION}/bin/"
    "${CMAKE_BINARY_DIR}/${CONFIGURATION}/"
)