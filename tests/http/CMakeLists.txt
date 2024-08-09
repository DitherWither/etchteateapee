add_executable(
    test_headers
    test_headers.cc
)

target_link_libraries(
    test_headers
    GTest::gtest_main
    etch
)

gtest_discover_tests(test_headers)