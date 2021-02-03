cmake_minimum_required(VERSION 3.5)
project(dp)
set(CMAKE_CXX_STANDARD 11)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(dp
        src/dp.cc
        src/dp.h
        src/main.cc
        src/handle_geojson.cc
        src/handle_geojson.h
        )
        
        
target_link_libraries(dp
        nlohmann_json::nlohmann_json
        )      
