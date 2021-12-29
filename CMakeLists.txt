cmake_minimum_required(VERSION 3.17)
project(semestalni_prace_pjc)


set(CMAKE_CXX_FLAGS -pthread)
#find_package(Threads REQUIRED)
#target_link_libraries(semestalni_prace_pjc PRIVATE Threads::Threads)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(semestalni_prace_pjc main.cpp Entity.cpp Mapa.cpp Result.cpp Grid.cpp Priority.cpp)