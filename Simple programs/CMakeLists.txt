cmake_minimum_required(VERSION 3.0.0)
project(simple)
enable_language(Fortran)
find_package(MPI REQUIRED)

add_executable(simple test1.c)

target_link_libraries(simple MPI::MPI_C)

add_executable(useable useable.c)
target_link_libraries(useable MPI::MPI_C)

add_executable(fortran_simpe test1.f)
target_link_libraries(fortran_simpe MPI::MPI_Fortran)
