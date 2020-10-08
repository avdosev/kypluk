cmake_minimum_required(VERSION 3.12)
project(kypluk)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

option(BUILD_TESTS "enable build tests" ON)
option(BUILD_BENCHMARKS "enable build benchmarks" ON)
option(CHECK_TEST_COVERAGE "enable coverage reporting" OFF)

# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if(BUILD_TESTS)
        if (CHECK_TEST_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            # Code Coverage Configuration
            add_library(coverage_config INTERFACE)
            target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )
            if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
                target_link_options(coverage_config INTERFACE --coverage)
            else()
                target_link_libraries(coverage_config INTERFACE --coverage)
            endif()
        endif()
        enable_testing()
        add_subdirectory( test ./test )
    endif()

    if(BUILD_BENCHMARKS)
        add_subdirectory(benchmarks ./benchmarks)
    endif()
endif()
