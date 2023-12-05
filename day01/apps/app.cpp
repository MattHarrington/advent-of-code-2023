#include <cassert>
#include <print>

#include "libaoc.hpp"

int main()
{
    std::print("Advent of Code 2023 Day 1\n");

    auto puzzle_input{ read_input("puzzle_input.txt") };

    const auto part1_answer{ part1(puzzle_input) };
    std::print("Part 1 answer: {}\n", part1_answer);
    assert(part1_answer == 55'029);

    const auto part2_answer{ part2(puzzle_input) };
    std::print("Part 2 answer: {}\n", part2_answer);
    assert(part2_answer == 55'686);

    return 0;
}
