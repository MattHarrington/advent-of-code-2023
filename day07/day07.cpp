import std;
import day07mod;
#include <assert.h>

int main()
{
	const auto sample_input{ read_input("sample_input.dat") };
	const auto puzzle_input{ read_input("puzzle_input.dat") };

	const auto part1_sample_answer{ part1(sample_input) };
	std::println("Part 1 sample answer: {}", part1_sample_answer);
	assert(6440 == part1_sample_answer);

	const auto part1_answer{ part1(puzzle_input) };
	std::println("Part 1 answer: {}", part1_answer);
	assert(254024898 == part1_answer);
}
