#include "libday03.h"

#include <cctype>
#include <fstream>
#include <numeric>
#include <regex>

std::vector<std::string> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::vector<std::string> schematic;
    std::string line;

    while (getline(in, line))
    {
        schematic.emplace_back(line);
    }

    return schematic;
}

int part1(const std::vector<std::string>& schematic)
{
    std::vector<int> part_numbers;

    const std::regex r{ R"((\d+))" };

    for (auto row{ 0 }; row < schematic.size(); ++row)
    {
        std::string line{ schematic.at(row) };
        for (auto i{std::sregex_iterator(std::cbegin(line), std::cend(line), r)}; i != std::sregex_iterator(); ++i)
        {
            auto match{ *i };
            auto match_pos{ match.position()};
            auto match_length{ match.length(1) };
            bool part_found_row_above{ false };

            // Check left
            if (match_pos > 0 && line.at(match_pos - 1) != '.' )
            {
                part_numbers.push_back(std::stoi(match.str()));
                continue;
            }

            // Check right
            else if (static_cast<size_t>(match_pos) < line.size() - match_length && (line.at(match_pos + match_length) != '.'))
            {
                part_numbers.push_back(std::stoi(match.str()));
                continue;
            }

            // Check row above
            if (row > 0)
            {
                for (auto i{ 0 }; i < match_length + 2; ++i)
                {
                    auto prev_row{ schematic.at(row - 1) };
                    if (match_pos + i > 0 && match_pos + i < line.size() && prev_row.at(match_pos + i - 1) != '.' )
                    {
                        part_numbers.push_back(std::stoi(match.str()));
                        part_found_row_above = true; // Prevents checking row below
                        break;
                    }
                }
            }

            // Check row below
            if (!part_found_row_above && row < schematic.size() - 1)
            {
                auto next_row{ schematic.at(row + 1) };
                for (auto i{ 0 }; i < match_length + 2; ++i)
                {
                    if (match_pos + i > 0 && match_pos + i < line.size() && next_row.at(match_pos + i - 1) != '.' )
                    {
                        part_numbers.push_back(std::stoi(match.str()));
                        break;
                    }
                }
            }
        }
    }

    return std::accumulate(std::cbegin(part_numbers), std::cend(part_numbers), 0);
}
