project(serialization_examples)

cmake_minimum_required(VERSION 3.0.2)

if(${CMAKE_VERSION} VERSION_GREATER 3.0)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF) # on g++ this ensures: -std=c++14 and not -std=gnu++14
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")

enable_testing()

add_subdirectory(avro)
add_subdirectory(protobuf)


