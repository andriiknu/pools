cmake_minimum_required(VERSION 3.9)
project(mpi_integral)


add_library(integral integral.c)

add_executable(sequential sequential.c)
target_link_libraries(sequential integral)


find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})   
set(LIB ${MPI_LIBRARIES})     

add_executable(mpi mpi.c)


target_link_libraries(mpi integral ${LIB})




                                                                                                                                          
                                                                                                                                                                        
                                                                                                                                           
                                                                                                                      
                                                                                                                                       
                                                                                                                                    
