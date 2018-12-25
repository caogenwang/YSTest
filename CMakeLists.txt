CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
PROJECT(hello)
SET(SRC_LIST
    main.cpp
    learn_test/con_procucer/con_prodcer.cpp
    learn_test/ThreadPool/ThreadPool.cpp
    learn_test/class/class_test.cpp
)
add_executable(hello ${SRC_LIST})
