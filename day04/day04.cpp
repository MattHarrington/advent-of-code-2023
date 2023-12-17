import std;
import day04mod;
#include <assert.h>

int main()
{
    const auto sample_input{ read_input("sample_input.dat") };
    assert(6 == sample_input.size());
    assert(5 == sample_input.front().first.size());
    assert(8 == sample_input.front().second.size());

    const auto puzzle_input{ read_input("puzzle_input.dat") };
    assert(199 == puzzle_input.size());
    assert(10 == puzzle_input.front().first.size());
    assert(25 == puzzle_input.front().second.size());

    const auto part1_sample_answer{ part1(sample_input) };
    std::println("Part 1 sample answer: {}", part1_sample_answer);
    assert(13 == part1_sample_answer);

    const auto part1_answer{ part1(puzzle_input) };
    std::println("Part 1 answer: {}", part1_answer);
    assert(23'847 == part1_answer);

    const auto part2_sample_answer{ part2(sample_input) };
    std::println("Part 2 sample answer: {}", part2_sample_answer);
    assert(30 == part2_sample_answer);

    const auto part2_answer{ part2(puzzle_input) };
    std::println("Part 2 answer: {}", part2_answer);
    assert(8'570'000 == part2_answer);
}
