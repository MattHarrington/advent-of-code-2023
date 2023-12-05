#include <algorithm>
#include <cctype>
#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "libaoc.hpp"

std::vector<std::string> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<std::string> calibration_values;
    std::string line;

    while (getline(in, line)) {
        calibration_values.push_back(line);
    }

    return calibration_values;
}

int part1(const std::vector<std::string>& calibration_values)
{
    int sum{ 0 };
    for (const auto& calibration_value : calibration_values)
    {
        // Search forwards for digit
        std::stringstream numeric_calibration_value_ss;
        auto first_digit_it = std::find_if(std::cbegin(calibration_value), std::cend(calibration_value),
            [](const auto& c) { return std::isdigit(c); });
        numeric_calibration_value_ss << *first_digit_it;

        // Search backwards for digit
        auto last_digit_it = std::find_if(std::crbegin(calibration_value), std::crend(calibration_value),
            [](const auto& c) { return std::isdigit(c); });
        numeric_calibration_value_ss << *last_digit_it;

        sum += std::stoi(numeric_calibration_value_ss.str());
    }

    return sum;
}

int part2(const std::vector<std::string>& calibration_values)
{
    int sum{ 0 };
    const auto r{ std::regex(R"((one|two|three|four|five|six|seven|eight|nine|\d))") };

    for (const auto& calibration_value_s : calibration_values)
    {
        std::smatch sm;
        std::vector<std::string> matches;

        auto start_pos{ std::cbegin(calibration_value_s) };
        while (std::regex_search(start_pos, std::cend(calibration_value_s), sm, r))
        {
            matches.emplace_back(sm[0]);
            //start_pos = sm.suffix().first; // fails on "9onekptdkglrnloneightfr"
            ++start_pos;
        }

        int first_digit{ 0 };
        int second_digit{ 0 };

        if (matches.front() == "one" || matches.front() == "1")
        {
            first_digit = 1;
        }
        else if (matches.front() == "two" || matches.front() == "2")
        {
            first_digit = 2;
        }
        else if (matches.front() == "three" || matches.front() == "3")
        {
            first_digit = 3;
        }
        else if (matches.front() == "four" || matches.front() == "4")
        {
            first_digit = 4;
        }
        else if (matches.front() == "five" || matches.front() == "5")
        {
            first_digit = 5;
        }
        else if (matches.front() == "six" || matches.front() == "6")
        {
            first_digit = 6;
        }
        else if (matches.front() == "seven" || matches.front() == "7")
        {
            first_digit = 7;
        }
        else if (matches.front() == "eight" || matches.front() == "8")
        {
            first_digit = 8;
        }
        else if (matches.front() == "nine" || matches.front() == "9")
        {
            first_digit = 9;
        }
        else
        {
            throw std::domain_error("No matched first digit");
        }

        if (matches.back() == "one" || matches.back() == "1")
        {
            second_digit = 1;
        }
        else if (matches.back() == "two" || matches.back() == "2")
        {
            second_digit = 2;
        }
        else if (matches.back() == "three" || matches.back() == "3")
        {
            second_digit = 3;
        }
        else if (matches.back() == "four" || matches.back() == "4")
        {
            second_digit = 4;
        }
        else if (matches.back() == "five" || matches.back() == "5")
        {
            second_digit = 5;
        }
        else if (matches.back() == "six" || matches.back() == "6")
        {
            second_digit = 6;
        }
        else if (matches.back() == "seven" || matches.back() == "7")
        {
            second_digit = 7;
        }
        else if (matches.back() == "eight" || matches.back() == "8")
        {
            second_digit = 8;
        }
        else if (matches.back() == "nine" || matches.back() == "9")
        {
            second_digit = 9;
        }
        else
        {
            throw std::domain_error("No matched second digit");
        }

        int calibration_value_i{ 10 * first_digit + second_digit };
        //std::cout << calibration_value_s << "\t" << calibration_value_i << "\n";
        sum += calibration_value_i;
    }

    return sum;
}
