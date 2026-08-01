cmake_minimum_required(VERSION 4.2)
project(ParaPlot)

set(CMAKE_CXX_STANDARD 20)

add_executable(ParaPlot main.cpp
        System.cpp
        System.h
        Plot.cpp
        Plot.h
        Structs.h
        Constants.h
        SystemDefinition.h
        SystemDefinition.cpp
        UIElements.cpp
        UIElements.h)

target_link_libraries(${PROJECT_NAME} raylib)