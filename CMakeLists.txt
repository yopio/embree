cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 11)

project(geometry)
project(instance)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Glm REQUIRED)
if(GLM_FOUND)
  include_directories(${GLM_INCLUDE_DIRS})
endif()

find_package(Embree3 REQUIRED)
if(EMBREE3_FOUND)
  include_directories(${EMBREE3_INCLUDE_DIRS})
endif()

find_package(OpenImageIO REQUIRED)
if(OPENIMAGEIO_FOUND)
  include_directories(${OPENIMAGEIO_INCLUDE_DIRS})
endif()

set(GEOMETRY_SRC_FILES
  ./src/geometry.cc
  ./src/pinhole_camera.cc)

set(INSTANCE_SRC_FILES
  ./src/instance.cc
  ./src/pinhole_camera.cc)

add_executable(geometry ${GEOMETRY_SRC_FILES})
add_executable(instance ${INSTANCE_SRC_FILES})

target_link_libraries(geometry
  embree3
  OpenImageIO)

target_link_libraries(instance
  embree3
  OpenImageIO)
