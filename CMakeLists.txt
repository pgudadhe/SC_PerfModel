cmake_minimum_required(VERSION 3.0.0)
project(SC_PerfModel VERSION 0.1.0 LANGUAGES C CXX)


include_directories("E:\\Documents\\Code\\systemc-2.3.4\\src")
link_directories("E:\\Documents\\Code\\systemc-2.3.4\\lib")

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    platform_top.cpp
    bus_master.cpp
    bus_target.cpp
    main.cpp
)

add_executable(SC_PerfModel ${SOURCES})
target_link_libraries(SC_PerfModel SystemC)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
