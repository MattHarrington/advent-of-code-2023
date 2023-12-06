#include <algorithm>
#include <cctype>
#include <fstream>
#include <regex>
#include <stdexcept>

#include "libaoc.hpp"

std::vector<std::string> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::vector<std::string> calibration_values;
    std::string line;

    while (getline(in, line))
    {
        calibration_values.push_back(line);
    }

    return calibration_values;
}

int part1(const std::vector<std::string>& calibration_values)
{
    int sum{ 0 };
    for (const auto& line : calibration_values)
    {
        // Search forwards for digit
        auto first_digit_it = std::find_if(std::cbegin(line), std::cend(line),
            [](const auto& c) { return std::isdigit(c); });
        int first_digit{ *first_digit_it - '0' };

        // Search backwards for digit
        auto last_digit_it = std::find_if(std::crbegin(line), std::crend(line),
            [](const auto& c) { return std::isdigit(c); });
        int second_digit{ *last_digit_it - '0' };

        sum += (10 * first_digit + second_digit);
    }

    return sum;
}

int part2(const std::vector<std::string>& calibration_values)
{
    int sum{ 0 };
    const auto r_forwards{ std::regex(R"((one|two|three|four|five|six|seven|eight|nine|\d))") };
    const auto r_backwards{ std::regex(R"((eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|\d))") };

    for (const auto& line : calibration_values)
    {
        std::smatch m_fwd;
        std::match_results<std::string::const_reverse_iterator> m_rev;
        std::string first_match;
        std::string last_match;

        if (std::regex_search(std::cbegin(line), std::cend(line), m_fwd, r_forwards))
        {
            first_match = m_fwd[0];
        }
        if (std::regex_search(std::crbegin(line), std::crend(line), m_rev, r_backwards))
        {
            last_match = m_rev[0];
        }

        int first_digit{ 0 };
        int second_digit{ 0 };

        if (first_match == "one" || first_match == "1")
        {
            first_digit = 1;
        }
        else if (first_match == "two" || first_match == "2")
        {
            first_digit = 2;
        }
        else if (first_match == "three" || first_match == "3")
        {
            first_digit = 3;
        }
        else if (first_match == "four" || first_match == "4")
        {
            first_digit = 4;
        }
        else if (first_match == "five" || first_match == "5")
        {
            first_digit = 5;
        }
        else if (first_match == "six" || first_match == "6")
        {
            first_digit = 6;
        }
        else if (first_match == "seven" || first_match == "7")
        {
            first_digit = 7;
        }
        else if (first_match == "eight" || first_match == "8")
        {
            first_digit = 8;
        }
        else if (first_match == "nine" || first_match == "9")
        {
            first_digit = 9;
        }
        else
        {
            throw std::invalid_argument("No matched first digit");
        }

        if (last_match == "eno" || last_match == "1")
        {
            second_digit = 1;
        }
        else if (last_match == "owt" || last_match == "2")
        {
            second_digit = 2;
        }
        else if (last_match == "eerht" || last_match == "3")
        {
            second_digit = 3;
        }
        else if (last_match == "ruof" || last_match == "4")
        {
            second_digit = 4;
        }
        else if (last_match == "evif" || last_match == "5")
        {
            second_digit = 5;
        }
        else if (last_match == "xis" || last_match == "6")
        {
            second_digit = 6;
        }
        else if (last_match == "neves" || last_match == "7")
        {
            second_digit = 7;
        }
        else if (last_match == "thgie" || last_match == "8")
        {
            second_digit = 8;
        }
        else if (last_match == "enin" || last_match == "9")
        {
            second_digit = 9;
        }
        else
        {
            throw std::invalid_argument("No matched second digit");
        }

        int calibration_value{ 10 * first_digit + second_digit };
        sum += calibration_value;
    }

    return sum;
}
