#include <algorithm>
#include <fstream>
#include <numeric>
#include <regex>
#include <vector>

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
    const std::regex r{ R"(([A-Z\d]+) = \(([A-Z\d]+), ([A-Z\d]+)\))" };
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
    auto instruction{ std::cbegin(map.instructions) };
    while (node != "ZZZ")
    {
        ++steps;
        node = (*instruction == 'L' ? map.network.at(node).first : map.network.at(node).second);
        if (std::next(instruction) == std::cend(map.instructions))
        {
            instruction = std::cbegin(map.instructions);
        }
        else
        {
            ++instruction;
        }
    }
    return steps;
}

long long part2(const Map& map)
{
    // Find starting nodes
    std::vector<std::string> nodes;
    for (const auto& node : map.network)
    {
        if (node.first.back() == 'A')
        {
            nodes.emplace_back(node.first);
        }
    }

    // Find when each node's value repeats throughout the instruction sequence
    std::vector<long long> periods;
    for (auto& node : nodes)
    {
        auto instruction{ std::cbegin(map.instructions) };
        auto steps{ 0LL };
        while (node.back() != 'Z')
        {
            ++steps;
            node = (*instruction == 'L' ? map.network.at(node).first : map.network.at(node).second);
            if (std::next(instruction) == std::cend(map.instructions))
            {
                instruction = std::cbegin(map.instructions);
            }
            else
            {
                ++instruction;
            }
        }
        periods.push_back(steps);
    }

    // Solution is LCM of all periods
    auto lcm{ std::accumulate(std::cbegin(periods), std::cend(periods), 1LL, std::lcm<long long, long long>) };
    return lcm;
}
