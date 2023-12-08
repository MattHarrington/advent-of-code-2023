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
    std::print("Part 1 sample answer: {}\n", part1_sample_answer);

    return 0;
}
