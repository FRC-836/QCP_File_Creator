#required on windows to link to qtmain.lib
cmake_minimum_required(VERSION 2.8.11)

project(QCP_File_Creator)

#instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

#Find the QtWidgets library
find_package(Qt5Widgets)

set(src src/main.cpp)
#no headers yet
#set(inc inc)

#setup inc as a valid include directory
include_directories(${CMAKE_SOURCE_DIR}/inc)

#create executable
add_executable(test ${src} ${inc})

#use the widgets moduole from Qt 5
target_link_libraries(test Qt5::Widgets)
