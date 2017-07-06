#required on windows to link to qtmain.lib
cmake_minimum_required(VERSION 2.8.11)

project(QCP_File_Creator)

#setup c++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_OPTIONS -o Inc/)

#Find the QtWidgets library
find_package(Qt5Widgets)

include_directories(Inc forms)

set(src src/main.cpp
        src/Creator.cpp
        src/Editor.cpp
        src/MainWindow.cpp
        src/NewDialog.cpp
        src/VarCreator.cpp
        src/SingleVarCreator.cpp
        src/MultiVarCreator.cpp
        src/QcpVariable.cpp
        src/QcpGroup.cpp
        src/Project.cpp
        src/QcpFile.cpp
        src/ConstCreator.cpp
        src/Manager.cpp
        src/CommandOptions.cpp
        )
set(inc Inc/Creator.h
        Inc/Editor.h
        Inc/MainWindow.h
        Inc/NewDialog.h
        Inc/VarCreator.h
        Inc/SingleVarCreator.h
        Inc/MultiVarCreator.h
        Inc/QcpVariable.h
        Inc/QcpGroup.h
        Inc/Project.h
        Inc/QcpFile.h
        Inc/ConstCreator.h
        Inc/Manager.h
        Inc/CommandOptions.h
        )
set(forms Inc/Creator.ui
          Inc/MainWindow.ui
          Inc/NewDialog.ui
          Inc/VarCreator.ui
          Inc/SingleVarCreator.ui
          Inc/MultiVarCreator.ui
          Inc/ConstCreatorDialog.ui
          )

#setup inc as a valid include directory
include_directories(${CMAKE_SOURCE_DIR}/inc)

#create executable
add_executable(QCP_File_Creator ${src} ${inc} ${forms})

#use the widgets moduole from Qt 5
target_link_libraries(QCP_File_Creator Qt5::Widgets)
