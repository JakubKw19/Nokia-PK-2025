project(UeApplication)
cmake_minimum_required(VERSION 3.12)

aux_source_directory(. SRC_LIST)
aux_source_directory(Ports SRC_LIST)
aux_source_directory(States SRC_LIST)

set(SRC_LIST ${SRC_LIST} Smsdb.cpp)


add_library(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} Common)

file(GLOB HEADER_LIST "States/*.h")
source_group("Header Files/States" FILES ${HEADER_LIST})