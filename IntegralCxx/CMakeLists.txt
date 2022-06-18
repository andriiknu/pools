cmake_minimum_required(VERSION 3.9)
project(mpi_integral)
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB src ${PROJECT_SOURCE_DIR}/src/*)
set(GLOB head ${PROJECT_SOURCE_DIR}/include/*)

add_library(integral ${src} ${head})



add_executable(sequential sequential.cpp)
target_link_libraries(sequential integral)


find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})   
set(LIB ${MPI_LIBRARIES})     

add_executable(mpi mpi.cpp)
target_link_libraries(mpi integral ${LIB})





                                                                                                                                          
                                                                                                                                                                        
                                                                                                                                           
                                                                                                                      
                                                                                                                                       
                                                                                                                                    
