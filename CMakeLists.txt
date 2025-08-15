cmake_minimum_required(VERSION 3.16)

project(custom_string LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(custom_string main.cpp
    String.h String.cpp)

include(GNUInstallDirs)
install(TARGETS custom_string
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
