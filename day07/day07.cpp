import std;
import day07mod;
#include <assert.h>

int main()
{
	const auto sample_input_part1{ read_input("sample_input.dat", PuzzlePart::one) };
	const auto puzzle_input_part1{ read_input("puzzle_input.dat", PuzzlePart::one) };

	const auto part1_sample_answer{ get_score(sample_input_part1) };
	std::println("Part 1 sample answer: {}", part1_sample_answer);
	assert(6440 == part1_sample_answer);

	const auto part1_answer{ get_score(puzzle_input_part1) };
	std::println("Part 1 answer: {}", part1_answer);
	assert(254'024'898 == part1_answer);

	const auto sample_input_part2{ read_input("sample_input.dat", PuzzlePart::two) };
	const auto puzzle_input_part2{ read_input("puzzle_input.dat", PuzzlePart::two) };

	const auto part2_sample_answer{ get_score(sample_input_part2) };
	std::println("Part 2 sample answer: {}", part2_sample_answer);
	assert(5905 == part2_sample_answer);

	const auto part2_answer{ get_score(puzzle_input_part2) };
	std::println("Part 2 answer: {}", part2_answer);
	assert(254'115'617 == part2_answer);
}
