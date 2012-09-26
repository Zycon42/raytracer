#
# CMakeLists.txt
# author: Jan Dušek <dus3k1an@gmail.com>

file(GLOB RAYTRACER_UTILS_HEADERS *.h)
file(GLOB RAYTRACER_UTILS_SOURCES *.cpp)

include_directories(${GLOG_INCLUDE_DIRS})

# on msvc we use static version of glog therefore we need to add proper definitions
if (MSVC)
	add_definitions(/D GOOGLE_GLOG_DLL_DECL=)
endif(MSVC)

add_library(utils STATIC ${RAYTRACER_UTILS_SOURCES} ${RAYTRACER_UTILS_HEADERS})
target_link_libraries(utils ${GLOG_LIBRARIES})
