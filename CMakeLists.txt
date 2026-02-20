cmake_minimum_required(VERSION 3.16)

project(PFSP)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

include_directories(include)

add_library(pfsp_libs
    src/morais.cpp
    src/eda.cpp
    src/edd.cpp
    src/pfs.cpp
)

# Crear ejecutable
add_executable(main_exec main/pfs_edd.cpp)

add_executable(pfs_test main/pfs_test.cpp)
add_executable(edd_test main/edd_test.cpp)
add_executable(eda_test main/eda_test.cpp)
add_executable(morais_test main/morais_test.cpp)



target_link_libraries(main_exec pfsp_libs)

target_link_libraries(pfs_test pfsp_libs)
target_link_libraries(edd_test pfsp_libs)
target_link_libraries(eda_test pfsp_libs)
target_link_libraries(morais_test pfsp_libs)

target_link_libraries(main_exec
    pfsp_libs
    OpenMP::OpenMP_CXX
)

target_link_libraries(pfs_test
    pfsp_libs
    OpenMP::OpenMP_CXX
)
target_link_libraries(edd_test
    pfsp_libs
    OpenMP::OpenMP_CXX
)
target_link_libraries(eda_test
    pfsp_libs
    OpenMP::OpenMP_CXX
)
target_link_libraries(morais_test
    pfsp_libs
    OpenMP::OpenMP_CXX
)