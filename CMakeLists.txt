cmake_minimum_required(VERSION 3.22)
project(petri)

include_directories(include)
add_subdirectory(submodules/yaucl_graph)
include_directories(submodules/yaucl_graph/include)
set(CMAKE_CXX_STANDARD 23)

add_executable(petri main.cpp
                     src/giacomobergami/petri/petri.cpp
                     include/giacomobergami/petri/petri.h
                     src/giacomobergami/petri/elementary_net.cpp
                     include/giacomobergami/petri/elementary_net.h
                     src/giacomobergami/petri/reachability_graph.cpp
                     include/giacomobergami/petri/reachability_graph.h
                     include/giacomobergami_petri.h)
target_link_libraries(petri yaucl_hashing yaucl_graph)
