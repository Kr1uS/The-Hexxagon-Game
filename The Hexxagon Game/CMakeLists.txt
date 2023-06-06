cmake_minimum_required(VERSION 3.25)
project(The_Hexxagon_Game)

set(CMAKE_CXX_STANDARD 23)
set(SRC_FILES
        main.cpp
        Table.cpp Table.h
        Player.cpp Player.h
        Computer.cpp Computer.h
        FileManager.cpp FileManager.h
        )

add_executable(${PROJECT_NAME} ${SRC_FILES})
