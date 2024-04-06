#include <assert.h>
#include <print>

#include "libday08.hpp"

int main()
{
	const auto sample_input{ read_input("sample_input.dat") };
	assert(sample_input.instructions.size() == 3);
	assert(sample_input.network.size() == 3);

	const auto puzzle_input{ read_input("puzzle_input.dat") };
	assert(puzzle_input.instructions.size() == 263);
	assert(puzzle_input.network.size() == 770);

	const auto part1_sample_answer{ part1(sample_input) };
	std::println("Part 1 sample answer: {}", part1_sample_answer);
	assert(part1_sample_answer == 6);

	const auto part1_answer{ part1(puzzle_input) };
	std::println("Part 1 answer: {}", part1_answer);
	assert(part1_answer == 16'043);
}
