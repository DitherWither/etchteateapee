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
    include/etch/core.h
    include/etch/core/utils.h
    include/etch/core/config.h
    include/etch/http.h
    include/etch/http/response.h
    include/etch/http/header.h
    include/etch/http/request.h
    include/etch/http/server.h
    include/etch.h
)

include_directories(include)

# Create shared library
add_library(etch SHARED ${SOURCE_FILES})

# Install library
install(TARGETS etch DESTINATION lib/etch)

# Install library headers
install(FILES ${HEADER_FILES} DESTINATION include/etch)
