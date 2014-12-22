##### SOURCES #####
aux_source_directory(. SRC_LIST)

##### BUILD and LINK #####
ADD_LIBRARY(${PROJECT_NAME}_Core ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}_Core Qt5::Widgets)
