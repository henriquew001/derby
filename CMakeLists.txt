project(Derby)

cmake_minimum_required(VERSION 3.0)

#set( PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build )

##### QT 5 #####
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

# Targets
add_subdirectory(src)

include_directories(
 ${CMAKE_SOURCE_DIR}/src
)

##### SOURCES #####
aux_source_directory(. SRC_LIST)

set( a_RCS
 ${CMAKE_SOURCE_DIR}/rc/images.qrc
)

set( a_UIS
 ${CMAKE_SOURCE_DIR}/src/mainwindow.ui
)

##### BUILD and LINK #####
add_executable(${PROJECT_NAME} ${SRC_LIST} ${a_RCS} ${a_UIS})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_Core Qt5::Widgets)
