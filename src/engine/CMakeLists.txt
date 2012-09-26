#
# CMakeLists.txt
# author: Jan Dušek <dus3k1an@gmail.com>

include_directories(${PROJECT_SOURCE_DIR}/src/utils)

file(GLOB RAYTRACER_ENGINE_HEADERS *.h)
file(GLOB RAYTRACER_ENGINE_SOURCES *.cpp)

add_library(engine STATIC ${RAYTRACER_ENGINE_SOURCES} ${RAYTRACER_ENGINE_HEADERS})
target_link_libraries(engine utils)
