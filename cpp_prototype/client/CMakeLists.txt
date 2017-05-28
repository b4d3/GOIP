#setting the project variables
set(TARGET_APPLICATION_NAME "udp-client")
set(HEADERS_DIRECTORY "include")
set(SOURCES_DIRECTORY "src")
set(BUILD_DIRECTORY "build")
set (CMAKE_CXX_STANDARD 11)
###########################################

project(UDP_client_provider)
cmake_minimum_required(VERSION 2.8.12)

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