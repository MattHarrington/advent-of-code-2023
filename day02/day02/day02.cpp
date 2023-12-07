#include <cassert>
#include <print>

#include "libday02.h"

int main()
{
    auto sample_input{ read_input("sample_input.txt") };
    auto puzzle_input{ read_input("puzzle_input.txt") };
    assert(5 == sample_input.size());
    assert(100 == puzzle_input.size());

    const auto part1_sample_answer{ part1(sample_input) };
    std::print("Part 1 sample answer: {}\n", part1_sample_answer);
    assert(8 == part1_sample_answer);

    const auto part1_answer{ part1(puzzle_input) };
    std::print("Part 1 answer: {}\n", part1_answer);
    assert(2795 == part1_answer);

    const auto part2_sample_answer{ part2(sample_input) };
    std::print("Part 2 sample answer: {}\n", part2_sample_answer);
    assert(2286 == part2_sample_answer);

    const auto part2_answer{ part2(puzzle_input) };
    std::print("Part 2 answer: {}\n", part2_answer);
    assert(75'561 == part2_answer);
}
