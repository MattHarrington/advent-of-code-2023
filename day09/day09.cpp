#include <assert.h>
#include <print>

#include "libday09.hpp"

int main()
{
    const auto sample_input{ read_input("sample_input.dat") };
    const auto puzzle_input{ read_input("puzzle_input.dat") };

    const auto part1_sample_answer{ part1(sample_input) };
    std::println("Part 1 sample answer: {}", part1_sample_answer);
    assert(part1_sample_answer == 114);

    const auto part1_answer{ part1(puzzle_input) };
    std::println("Part 1 answer: {}", part1_answer);
    assert(part1_answer == 1'898'776'583);
}
