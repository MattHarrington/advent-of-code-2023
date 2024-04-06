#include <fstream>
#include <regex>

#include "libday08.hpp"

Map read_input(const std::string& filename)
{
	std::fstream in{ std::fstream(filename) };
	if (!in)
	{
		throw std::runtime_error("File not found");
	}

	Map map;

	std::string instructions;
	getline(in, instructions);
	map.instructions = instructions;

	std::string line;
	getline(in, line); // Skip a line

	std::map<std::string, std::pair<std::string, std::string>> network;
	const std::regex r{ R"(([A-Z]+) = \(([A-Z]+), ([A-Z]+)\))" };
	std::smatch sm;

	while (getline(in, line))
	{
		std::regex_match(line, sm, r);
		const auto pair{ std::make_pair<std::string, std::string>(sm[2], sm[3]) };
		network[sm[1]] = pair;
	}

	map.network = network;
	return map;
}

int part1(const Map& map)
{
	auto steps{ 0 };
	std::string node{ "AAA" };
	auto it{ std::cbegin(map.instructions) };
	while (node != "ZZZ")
	{
		++steps;
		node = (*it == 'L' ? map.network.at(node).first : map.network.at(node).second);
		if (std::next(it) == std::cend(map.instructions))
		{
			it = std::cbegin(map.instructions);
		}
		else
		{
			++it;
		}
	}
	return steps;
}
