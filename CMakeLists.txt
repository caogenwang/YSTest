CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
PROJECT(array)
SET(SRC_LIST
    offer/1.array.cpp
)
add_executable(array ${SRC_LIST})
