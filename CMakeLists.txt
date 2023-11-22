cmake_minimum_required(VERSION 3.14)

project(GraphLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
  #headers
  include/ggh/GraphLib_global.h
  include/ggh/graph_lib.h
  include/ggh/graph.h

  #sources
  src/graph_lib.cpp
  src/graph.cpp
  README.md
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GRAPHLIB_LIBRARY )

add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
