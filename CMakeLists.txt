cmake_minimum_required(VERSION 3.20)
project(engine LANGUAGES C)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/src)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/deps)

#----------------------------------------------
# Dependencies
#----------------------------------------------

# ---- glfw ---------------------------
option(GLFW_BUILD_DOCS     OFF)
option(GLFW_BUILD_TESTS    OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_INSTALL        OFF)

add_subdirectory(${LIB_DIR}/glfw)

# ---- glad ---------------------------
add_subdirectory(${LIB_DIR}/glad)

# ---- stb ----------------------------
add_subdirectory(${LIB_DIR}/stb)

# ---- OpenGL -------------------------
find_package(OpenGL REQUIRED)


#----------------------------------------------
# Project
#----------------------------------------------

set(ENGINE_HEADERS
    ${INC_DIR}/core.h
    ${INC_DIR}/graphics.h
    ${INC_DIR}/maths.h
)

set(ENGINE_SOURCES
    ${SRC_DIR}/core.c
    ${SRC_DIR}/graphics.c
    ${SRC_DIR}/maths.c
)

set(TEST_HEADERS
)

set(TEST_SOURCES
    ${SRC_DIR}/test.c
)

add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    glad
    stb
    ${OPENGL_gl_LIBRARY})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${INC_DIR}
    glfw
    glad
    stb
    ${OPENGL_INCLUDE_DIR})

target_compile_options(${PROJECT_NAME} PUBLIC
    -std=c99
    -Wall
    -Wextra
    -Wpedantic
    -Werror)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(${PROJECT_NAME}_test PUBLIC ${PROJECT_NAME})