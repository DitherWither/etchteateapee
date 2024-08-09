cmake_minimum_required(VERSION 3.30)
project(etch VERSION 0.2)

include(CTest)
add_subdirectory(tests)
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

# Create shared library
add_library(etch SHARED ${SOURCE_FILES})
target_include_directories(etch PUBLIC include)

# Install library
install(TARGETS etch DESTINATION lib/etch)

# Install library headers
install(FILES ${HEADER_FILES} DESTINATION include/etch)
