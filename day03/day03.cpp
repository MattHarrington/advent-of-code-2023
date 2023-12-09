#include <cassert>
#include <print>

#include "libday03.h"

int main()
{
    const auto sample_input{ read_input("sample_input.dat") };
    const auto puzzle_input{ read_input("puzzle_input.dat") };
    assert(10 == sample_input.size());
    assert(140 == puzzle_input.size());

    const auto part1_sample_answer{ part1(sample_input) };
    std::println("Part 1 sample answer: {}", part1_sample_answer);
    assert(4361 == part1_sample_answer);

    const auto part1_answer{ part1(puzzle_input) };
    std::println("Part 1 answer: {}", part1_answer);
    assert(550'934 == part1_answer);

    const auto part2_sample_answer{ part2(sample_input) };
    std::println("Part 2 sample answer: {}", part2_sample_answer);
    assert(467'835 == part2_sample_answer);

    const auto part2_answer{ part2(puzzle_input) };
    std::println("Part 2 answer: {}", part2_answer);
    assert(81'997'870 == part2_answer);

    return 0;
}
