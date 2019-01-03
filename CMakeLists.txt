cmake_minimum_required(VERSION 3.10)
project(WATERTANK_SYSTEM)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories($ENV{SYSTEMC_HOME}/include)

find_library(systemc systemc $ENV{SYSTEMC_HOME}/lib-linux64)
link_directories($ENV{SYSTEMC_HOME}/lib-linux64)

add_executable(watertank_system
        src/valve_TDF.cpp
        src/valve_iface.cpp
        src/watertank_LSF.cpp
        src/XTEA_RTL.cpp
        src/XTEA_RTL_transactor.cpp
        src/controller_TLM.cpp
        src/watertank_iface.cpp
        src/watertank_LSF_transactor.cpp
        src/watertank_system.cpp
        src/main.cpp)
target_link_libraries(watertank_system systemc systemc-ams)
