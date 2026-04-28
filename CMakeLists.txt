cmake_minimum_required(VERSION 3.21)
project(audioAnalyser)

set(CMAKE_CXX_STANDARD 14)

# Trouver Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(app_exec
        AudioReader.cpp
        WaveformWidget.cpp
        MainWindow.cpp
        main.cpp)

# Lier Qt
target_link_libraries(app_exec Qt6::Widgets)