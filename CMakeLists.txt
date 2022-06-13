cmake_minimum_required(VERSION 2.8.12)

project(TerminalDrawer)
SET("OpenCV_DIR" "/Users/franciszekszewczyk/Documents/opencv/build_opencv")
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

set(LIBRARIES
    ${OpenCV_LIBS}
)

file(GLOB SOURCES
    main.cpp
)

add_executable(TerminalDrawer ${SOURCES})
target_link_libraries(TerminalDrawer ${LIBRARIES})
target_compile_options(TerminalDrawer PRIVATE -Wno-psabi)
