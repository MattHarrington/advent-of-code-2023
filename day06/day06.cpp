import std;
import day06mod;
#include <assert.h>

int main()
{
    const auto sample_input{ read_input("sample_input.dat") };
    const auto puzzle_input{ read_input("puzzle_input.dat") };

    const auto part1_sample_answer{ part1(sample_input) };
    std::println("Part 1 sample answer: {}", part1_sample_answer);
    assert(288 == part1_sample_answer);

    const auto part1_answer{ part1(puzzle_input) };
    std::println("Part 1 answer: {}", part1_answer);
    assert(3'316'275 == part1_answer);

    const auto part2_sample_answer{ part2(sample_input) };
    std::println("Part 2 sample answer: {}", part2_sample_answer);
    assert(71'503 == part2_sample_answer);

    const auto part2_answer{ part2(puzzle_input) };
    std::println("Part 2 answer: {}", part2_answer);
    assert(27'102'791 == part2_answer);
}
