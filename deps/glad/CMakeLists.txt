project(glad)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCES ${SRC_DIR}/glad.c)
set(HEADERS ${INC_DIR}/glad/glad.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
