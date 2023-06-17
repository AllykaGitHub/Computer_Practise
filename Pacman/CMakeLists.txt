cmake_minimum_required(VERSION 3.23)
project(Pacman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pacman main.cpp
        Entity.h Entity.cpp
        Game.h Game.cpp
        Ghost.h Ghost.cpp
        Pacman.h Pacman.cpp
        Cell.h AbstractGhostFactory.h Field.h AbstractGhostFactory.cpp Cell.cpp UIPanel.cpp UIPanel.h)

set(SFML_DIR "C:/Users/lyaho/CS_Projects/C++/lib/SFML/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/lib/cmake/SFML")
target_link_libraries(Pacman sfml-graphics)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules ")
find_package(SFML 2.5.1 REQUIRED graphics network audio system)