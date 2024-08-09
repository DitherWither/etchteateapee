cmake_minimum_required(VERSION 3.30)
project(etch VERSION 0.2)

set(
    SOURCE_FILES
    etch/core/utils.c
    etch/core/config.c
    etch/http/request.c
    etch/http/response/serve_file.c
    etch/http/response/parse.c
    etch/http/server.c
    etch/http/header.c
)
set(
    HEADER_FILES
    etch/include/etch/core.h
    etch/include/etch/core/utils.h
    etch/include/etch/core/config.h
    etch/include/etch/http.h
    etch/include/etch/http/response.h
    etch/include/etch/http/header.h
    etch/include/etch/http/request.h
    etch/include/etch/http/server.h
    etch/include/etch.h
)

include_directories(etch/include)

# Create shared library
add_library(etch SHARED ${SOURCE_FILES})

# Install library
install(TARGETS etch DESTINATION lib/etch)

# Install library headers
install(FILES ${HEADER_FILES} DESTINATION include/etch)
