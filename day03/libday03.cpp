#include "libday03.h"

#include <cctype>
#include <fstream>
#include <numeric>
#include <regex>
#include <utility>

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
        const std::string line{ schematic.at(row) };
        for (auto i{ std::sregex_iterator(std::cbegin(line), std::cend(line), r) }; i != std::sregex_iterator(); ++i)
        {
            auto match{ *i };
            const auto match_pos{ match.position() };
            const auto match_length{ match.length(1) };
            bool part_found_row_above{ false };

            // Check left
            if (match_pos > 0 && line.at(match_pos - 1) != '.')
            {
                part_numbers.push_back(std::stoi(match.str()));
                continue;
            }

            // Check right. Use std::cmp_less() here and elsewhere because of signed/unsigned mismatch.
            else if (std::cmp_less(match_pos, line.size() - match_length) && (line.at(match_pos + match_length) != '.'))
            {
                part_numbers.push_back(std::stoi(match.str()));
                continue;
            }

            // Check row above
            if (row > 0)
            {
                for (auto j{ 0 }; j < match_length + 2; ++j)
                {
                    const auto prev_row{ schematic.at(row - 1) };
                    if (match_pos + j > 0 && std::cmp_less(match_pos + j, line.size()) && prev_row.at(match_pos + j - 1) != '.')
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
                const auto next_row{ schematic.at(row + 1) };
                for (auto j{ 0 }; j < match_length + 2; ++j)
                {
                    if (match_pos + j > 0 && std::cmp_less(match_pos + j, line.size()) && next_row.at(match_pos + j - 1) != '.')
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

int get_complete_number(const std::string& row, std::ptrdiff_t pos)
{
    // Pos could be in the middle of a number, so back up
    while (pos > 0 && std::isdigit(row.at(pos - 1)))
    {
        --pos;
    }

    // Find the number beginning at pos
    const std::regex r{ R"((\d+))" };
    auto start_it{ std::cbegin(row) + pos };
    std::smatch sm;

    std::regex_search(start_it, std::cend(row), sm, r);
    const int complete_number{ std::stoi(sm[1]) };

    return complete_number;
}

int part2(const std::vector<std::string>& schematic)
{
    // Find a gear (*)
    // Check the 8 positions around the gear to see if any two part numbers touch it
    // Multiply those two part numbers and add to sum_of_gear_ratios

    int sum_of_gear_ratios{ 0 };
    const std::regex r{ R"(\*)" };

    for (size_t row{ 0 }; row < schematic.size(); ++row)
    {
        const std::string line{ schematic.at(row) };
        for (auto i{ std::sregex_iterator(std::cbegin(line), std::cend(line), r) }; i != std::sregex_iterator(); ++i)
        {
            const auto match{ *i }; // Gear
            const auto match_pos{ match.position() };
            std::vector<int> numbers_touching_gear;
            bool in_middle_of_number{ false }; // Prevents matching the same number from two different positions

            // Start in NW position and move clockwise around the gear
            if (row > 0 && match_pos > 0)
            {
                const auto prev_row{ schematic.at(row - 1) };
                if (std::isdigit(prev_row.at(match_pos - 1)))
                {
                    const auto complete_number{ get_complete_number(prev_row, match_pos - 1) };
                    numbers_touching_gear.push_back(complete_number);
                    in_middle_of_number = true;
                }
            }
            // N
            if (row > 0)
            {
                const auto prev_row{ schematic.at(row - 1) };
                if (prev_row.at(match_pos) == '.')
                {
                    in_middle_of_number = false;
                }
                else if (!in_middle_of_number && std::isdigit(prev_row.at(match_pos)))
                {
                    const auto complete_number{ get_complete_number(prev_row, match_pos) };
                    numbers_touching_gear.push_back(complete_number);
                    in_middle_of_number = true;
                }
            }
            // NE
            if (row > 0 && std::cmp_less(match_pos, line.size() - 1))
            {
                const auto prev_row{ schematic.at(row - 1) };
                if (!in_middle_of_number && std::isdigit(prev_row.at(match_pos + 1)))
                {
                    const auto complete_number{ get_complete_number(prev_row, match_pos + 1) };
                    numbers_touching_gear.push_back(complete_number);
                }
                in_middle_of_number = false;
            }
            // E
            if (std::cmp_less(match_pos, line.size() - 1))
            {
                if (std::isdigit(line.at(match_pos + 1)))
                {
                    const auto complete_number{ get_complete_number(line, match_pos + 1) };
                    numbers_touching_gear.push_back(complete_number);
                }
            }
            // SE
            if (row < schematic.size() - 1 && std::cmp_less(match_pos, line.size() - 1))
            {
                const auto next_row{ schematic.at(row + 1) };
                if (std::isdigit(next_row.at(match_pos + 1)))
                {
                    const auto complete_number{ get_complete_number(next_row, match_pos + 1) };
                    numbers_touching_gear.push_back(complete_number);
                    in_middle_of_number = true;
                }
            }
            // S
            if (row < schematic.size() - 1)
            {
                const auto next_row{ schematic.at(row + 1) };
                if (next_row.at(match_pos) == '.')
                {
                    in_middle_of_number = false;
                }
                else if (!in_middle_of_number && std::isdigit(next_row.at(match_pos)))
                {
                    const auto complete_number{ get_complete_number(next_row, match_pos) };
                    numbers_touching_gear.push_back(complete_number);
                    in_middle_of_number = true;
                }
            }
            // SW
            if (row < schematic.size() - 1 && match_pos > 0)
            {
                const auto next_row{ schematic.at(row + 1) };
                if (!in_middle_of_number && std::isdigit(next_row.at(match_pos - 1)))
                {
                    const auto complete_number{ get_complete_number(next_row, match_pos - 1) };
                    numbers_touching_gear.push_back(complete_number);
                }
                in_middle_of_number = false;
            }
            // W
            if (match_pos > 0)
            {
                if (std::isdigit(line.at(match_pos - 1)))
                {
                    const auto complete_number{ get_complete_number(line, match_pos - 1) };
                    numbers_touching_gear.push_back(complete_number);
                }
            }

            // Did we find two part numbers?
            if (numbers_touching_gear.size() == 2)
            {
                const int gear_ratio{ numbers_touching_gear.at(0) * numbers_touching_gear.at(1) };
                sum_of_gear_ratios += gear_ratio;
            }
        }
    }

    return sum_of_gear_ratios;
}
