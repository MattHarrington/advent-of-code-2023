#include <assert.h>
#include <print>

#include "libday09.hpp"

int main()
{
    const auto part1_sample_input{ read_input("sample_input.dat", PuzzlePart::one) };
    const auto part1_puzzle_input{ read_input("puzzle_input.dat", PuzzlePart::one) };
    const auto part2_sample_input{ read_input("sample_input.dat", PuzzlePart::two) };
    const auto part2_puzzle_input{ read_input("puzzle_input.dat", PuzzlePart::two) };

    const auto part1_sample_answer{ solve(part1_sample_input) };
    std::println("Part 1 sample answer: {}", part1_sample_answer);
    assert(part1_sample_answer == 114);

    const auto part1_answer{ solve(part1_puzzle_input) };
    std::println("Part 1 answer: {}", part1_answer);
    assert(part1_answer == 1'898'776'583);

    const auto part2_sample_answer{ solve(part2_sample_input) };
    std::println("Part 2 sample answer: {}", part2_sample_answer);
    assert(part2_sample_answer == 2);

    const auto part2_answer{ solve(part2_puzzle_input) };
    std::println("Part 2 answer: {}", part2_answer);
    assert(part2_answer == 1100);
}
