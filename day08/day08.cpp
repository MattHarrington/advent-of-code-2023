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

	const auto sample_input_part2{ read_input("sample_input_part2.dat") };
	assert(sample_input_part2.instructions.size() == 2);
	assert(sample_input_part2.network.size() == 8);

	const auto part1_sample_answer{ part1(sample_input) };
	std::println("Part 1 sample answer: {}", part1_sample_answer);
	assert(part1_sample_answer == 6);

	const auto part1_answer{ part1(puzzle_input) };
	std::println("Part 1 answer: {}", part1_answer);
	assert(part1_answer == 16'043);

	const auto part2_sample_answer{ part2(sample_input_part2) };
	std::println("Part 2 sample answer: {}", part2_sample_answer);
	assert(part2_sample_answer == 6);

	const auto part2_answer{ part2(puzzle_input) };
	std::println("Part 2 answer: {}", part2_answer);
	assert(part2_answer == 15'726'453'850'399);
}
