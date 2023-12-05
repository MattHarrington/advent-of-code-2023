#include <catch.hpp>

#include "libaoc.hpp"

const auto sample_input_part1{ read_input("sample_input_part1.txt") };
const auto sample_input_part2{ read_input("sample_input_part2.txt") };
const auto puzzle_input{ read_input("puzzle_input.txt") };

TEST_CASE("Sample input for part 1 should contain 4 calibration values")
{
    CHECK(sample_input_part1.size() == 4);
}

TEST_CASE("Sample input for part 2 should contain 7 calibration values")
{
    CHECK(sample_input_part2.size() == 7);
}

TEST_CASE("Puzzle input should contain 1000 calibration values")
{
    CHECK(puzzle_input.size() == 1000);
}

TEST_CASE("Part 1 answer with sample input should be 142")
{
    const auto part1_answer{ part1(sample_input_part1) };
    CHECK(part1_answer == 142);
}

TEST_CASE("Part 1 answer with puzzle input should be 55'029")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 55'029);
}

TEST_CASE("Part 2 answer with sample input should be 281")
{
    const auto part2_answer{ part2(sample_input_part2) };
    CHECK(part2_answer == 281);
}

TEST_CASE("Part 2 answer with puzzle input should be 55'686")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 55'686);
}
