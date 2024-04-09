cmake_minimum_required (VERSION 2.8.11)
project (SAMPLE)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_CFLAGS} -std=c++11")

# add libsophon
find_package(libsophon REQUIRED)
include_directories(${LIBSOPHON_INCLUDE_DIRS})
link_directories(${LIBSOPHON_LIB_DIRS})

# add sophon-ffmpeg
set(FFMPEG_DIR	/opt/sophon/sophon-ffmpeg-latest/lib/cmake)
find_package(FFMPEG REQUIRED NO_DEFAULT_PATH)
include_directories(${FFMPEG_INCLUDE_DIRS})
link_directories(${FFMPEG_LIB_DIRS})

# add sophon-opencv
set(OpenCV_DIR /opt/sophon/sophon-opencv-latest/lib/cmake/opencv4)
find_package(OpenCV REQUIRED NO_DEFAULT_PATH)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRC_FILES *.cpp *.c)
STRING(REGEX REPLACE ".*/(.*)" "\\1" TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${TARGET_NAME} ${SRC_FILES})

target_link_libraries(${TARGET_NAME} ${FFMPEG_LIBS} ${OpenCV_LIBS} pthread stdc++)
