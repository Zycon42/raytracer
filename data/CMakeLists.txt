#
# CMakeLists.txt
# author: Jan Du�ek <dus3k1an@gmail.com>

# copy to binary dir so we can use them without need to install
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR}/${DATA_DIR})

install(DIRECTORY shaders DESTINATION ${DATA_DIR})