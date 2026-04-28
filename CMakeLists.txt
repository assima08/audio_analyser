cmake_minimum_required(VERSION 3.21)
project(audioAnalyser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(app_exec
        AudioReader.cpp
        WaveformWidget.cpp
        MainWindow.cpp
        main.cpp
        )

target_link_libraries(app_exec
        Qt6::Core
        Qt6::Widgets
        )