cmake_minimum_required(VERSION 3.27)

project(qt44 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Multimedia)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(qt44
  main.cpp
)
target_link_libraries(qt44 Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(qt44 Qt6::Multimedia)

include(GNUInstallDirs)
install(TARGETS qt44
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
