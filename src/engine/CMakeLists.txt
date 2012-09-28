#
# CMakeLists.txt
# author: Jan Dušek <dus3k1an@gmail.com>

file(GLOB RAYTRACER_ENGINE_HEADERS *.h)
file(GLOB RAYTRACER_ENGINE_SOURCES *.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src/utils)

add_library(engine STATIC ${RAYTRACER_ENGINE_SOURCES} ${RAYTRACER_ENGINE_HEADERS})
target_link_libraries(engine utils)
