#include "libday03.h"

#include <cctype>
#include <fstream>
#include <numeric>
#include <regex>

#include <print>

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
    std::smatch sm;

    for (auto row{ 0 }; row < schematic.size(); ++row)
    {
        std::string line{ schematic.at(row) };
        auto pos{ 0 };
        auto start_pos{ std::cbegin(line) };
        while (std::regex_search(start_pos, std::cend(line), sm, r))
        {
            pos += sm.position(1) + sm[1].length();
            auto col{ pos }; // incorrect when matching suffix

            auto num_length{ sm.length(1) };
            // Check left
            if (col > 0 && (line.at(col - 1) != '.' || !std::isdigit(line.at(col - 1))))
            {
                part_numbers.push_back(std::stoi(sm[1]));
            }
            // Check right
            else if (static_cast<size_t>(col) < line.size() && (line.at(col + num_length) != '.'))
            {
                part_numbers.push_back(std::stoi(sm[1]));
            }
            // Check row above
            else if (row > 0)
            {
                for (auto i{ 0 }; i < num_length + 2; ++i)
                {
                    auto prev_row{ schematic.at(row - 1) };
                    if (col + i > 0 && col + i < line.size() && ((prev_row.at(col + i - 1) != '.' || !std::isdigit(prev_row.at(col + i - 1)))))
                    {
                        part_numbers.push_back(std::stoi(sm[1]));
                        //goto check_row_below;
                        break;
                    }
                }
            }
            //check_row_below:
            if (row < schematic.size() - 1)
            {
                auto next_row{ schematic.at(row + 1) };
                for (auto i{ 0 }; i < num_length + 2; ++i)
                {
                    if (col + i > 0 && col + i < line.size() && ((next_row.at(col + i - 1) != '.' || !std::isdigit(next_row.at(col + i - 1)))))
                        //if (col + i > 0 && next_row.at(col + i - 1) != '.')
                    {
                        part_numbers.push_back(std::stoi(sm[1]));
                        //goto finished_with_row;
                        break;
                    }
                }
            }
            start_pos = sm.suffix().first;
            //finished_with_row:
        }
    }

    return std::accumulate(std::cbegin(part_numbers), std::cend(part_numbers), 0);
}
