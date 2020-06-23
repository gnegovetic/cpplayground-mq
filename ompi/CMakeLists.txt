cmake_minimum_required(VERSION 3.0)

project(hellompi)

set(CMAKE_BUILD_TYPE Release)

# find open-mpi
find_package(MPI REQUIRED)

# find Google benchmark 
#find_package(benchmark) 

# first test
add_executable(hellompi test.cpp)
#target_link_libraries(hellompi MPI_C)
target_link_libraries(hellompi ${MPI_C_LIBRARIES})

# server / client
add_executable(mpicomm connectivity.cpp)
target_link_libraries(mpicomm ${MPI_C_LIBRARIES})

# client benchmark
#add_executable(mpi_bm mpi_bm.cpp)
#target_link_libraries(mpi_bm ${MPI_C_LIBRARIES} benchmark)
