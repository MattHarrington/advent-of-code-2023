find_package(Catch2 3 REQUIRED)

IF (WIN32)
    configure_file(../apps/sample_input_part1.txt sample_input_part1.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/sample_input_part2.txt sample_input_part2.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/puzzle_input.txt puzzle_input.txt NEWLINE_STYLE WIN32)
ELSE ()
    configure_file(../apps/sample_input_part1.txt sample_input_part1.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/sample_input_part2.txt sample_input_part2.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/puzzle_input.txt puzzle_input.txt NEWLINE_STYLE UNIX)
ENDIF ()

# Tests need to be added as executables first
add_executable(aoc-tests testlib.cpp)

# Using C++17 in the test
target_compile_features(aoc-tests PRIVATE cxx_std_17)

# Increase warnings
if (MSVC)
    target_compile_options(aoc-tests PRIVATE /W4 /WX)
else ()
    target_compile_options(aoc-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(aoc-tests PRIVATE libaoc Catch2::Catch2WithMain)

# Automatically discover tests in target
include(Catch)
catch_discover_tests(aoc-tests)
