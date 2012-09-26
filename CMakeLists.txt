#
# CMakeLists.txt
# author: Jan Dušek <dus3k1an@gmail.com>

project(raytracer)
cmake_minimum_required(VERSION 2.8)		# we use file(COPY ...)

# add custom cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# find packages
find_package(SDL REQUIRED)
find_package(Glew REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Glog REQUIRED)

# set bin directory for runtime files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set static data directory
if (WIN32)
	set(DATA_DIR data)
else (WIN32)
	# on unix static data are stored in share directory
	set(DATA_DIR share/${PROJECT_NAME})
endif()

# create config.h
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config/config.h)
include_directories(${CMAKE_BINARY_DIR}/config)

add_subdirectory(data)
add_subdirectory(src)
add_subdirectory(test)

# install required system runtime libraries
include(InstallRequiredSystemLibraries)

# TODO: on WIN32 install and copy to /bin external dlls