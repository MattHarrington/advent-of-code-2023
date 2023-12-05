IF (WIN32)
    configure_file(sample_input_part1.txt sample_input_part1.txt NEWLINE_STYLE WIN32)
    configure_file(puzzle_input.txt puzzle_input.txt NEWLINE_STYLE WIN32)
ELSE ()
    configure_file(sample_input_part1.txt sample_input_part1.txt NEWLINE_STYLE UNIX)
    configure_file(puzzle_input.txt puzzle_input.txt NEWLINE_STYLE UNIX)
ENDIF ()

add_executable(app app.cpp)
target_compile_features(app PRIVATE cxx_std_23)

target_link_libraries(app PRIVATE libaoc)

# Increase warnings
if (MSVC)
    target_compile_options(app PRIVATE /W4 /WX)
else ()
    target_compile_options(app PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()
