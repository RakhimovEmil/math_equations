cmake_minimum_required (VERSION 3.8)

project(control-2)

set(CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX -O1 -g  -fno-omit-frame-pointer -fsanitize=address") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -Wall -Werror -fno-omit-frame-pointer -fsanitize=address -fsanitize=leaks")
endif()

add_executable(control-2-test src/expression.cpp src/test.cpp)
