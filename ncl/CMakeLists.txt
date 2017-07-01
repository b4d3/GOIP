#setting the project variables
set(TARGET_APPLICATION_NAME "ncl")
set(HEADERS_DIRECTORY "include")
set(SOURCES_DIRECTORY "src")
set(BUILD_DIRECTORY "build")
set(CMAKE_CXX_STANDARD 14)
###########################################

project(network_connectivity_layer)
cmake_minimum_required(VERSION 3.1.3)

#setting the soures and headers directory
file(GLOB_RECURSE SOURCES "${SOURCES_DIRECTORY}/*.cpp")
file(GLOB_RECURSE HEADERS "${HEADERS_DIRECTORY}/*.h")

#conan related things
include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#sets the variable CMAKE_THREADS_LIBS_INIT, so that threads can be included
find_package (Threads)

include_directories(${HEADERS_DIRECTORY})

#adding headers makes to make dependencies in makefile right
add_executable(${TARGET_APPLICATION_NAME} ${SOURCES} ${HEADERS})
#link the needed libraries (conan libs and threads)
target_link_libraries(${TARGET_APPLICATION_NAME} ${CONAN_LIBS} ${CMAKE_THREAD_LIBS_INIT})
