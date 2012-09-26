#
# CMakeLists.txt
# author: Jan Dušek <dus3k1an@gmail.com>

include_directories(
	${SDL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLOG_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/src/utils ${PROJECT_SOURCE_DIR}/src/engine
)

# on MSVC we use static libraries glew,libglog and therefore we need to add proper definitions
if (MSVC)
	add_definitions(/D GLEW_STATIC /D GOOGLE_GLOG_DLL_DECL=)
endif()

file(GLOB RAYTRACER_APPLICATION_HEADERS *.h)
file(GLOB RAYTRACER_APPLICATION_SOURCES *.cpp)

# on windows start with WinMain()
add_executable(${PROJECT_NAME} WIN32 ${RAYTRACER_APPLICATION_SOURCES} ${RAYTRACER_APPLICATION_HEADERS})
target_link_libraries(${PROJECT_NAME} engine utils ${GLOG_LIBRARIES} ${SDL_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
