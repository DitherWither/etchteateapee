cmake_minimum_required(VERSION 3.30)
project(etch VERSION 0.2)

set(
    SOURCE_FILES
    src/core/utils.c
    src/core/config.c
    src/http/request.c
    src/http/response/serve_file.c
    src/http/response/parse.c
    src/http/server.c
    src/http/header.c
)

include_directories(include)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
