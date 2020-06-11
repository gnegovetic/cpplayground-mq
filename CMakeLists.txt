cmake_minimum_required(VERSION 3.0)

project(zmqtest)

set(CMAKE_BUILD_TYPE Release)

# find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)

# find Google benchmark 
find_package(benchmark) 

# server
add_executable(server server.cpp)
target_link_libraries(server cppzmq)

# client
add_executable(client client.cpp)
target_link_libraries(client cppzmq)

# client benchmark
add_executable(client_bm client_bm.cpp)
target_link_libraries(client_bm cppzmq benchmark)
