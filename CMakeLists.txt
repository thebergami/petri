cmake_minimum_required(VERSION 3.22)
project(petri)

include_directories(include)
set(CMAKE_CXX_STANDARD 23)

add_executable(petri main.cpp src/giacomobergami/petri/petri.cpp include/giacomobergami/petri/petri.h src/giacomobergami/petri/elementary_net.cpp include/giacomobergami/petri/elementary_net.h src/giacomobergami/petri/reachability_graph.cpp include/giacomobergami/petri/reachability_graph.h include/giacomobergami_petri.h)
