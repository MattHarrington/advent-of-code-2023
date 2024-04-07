#include <algorithm>
#include <sstream>

#include "libday09.hpp"

Report read_input(const std::string& filename, const PuzzlePart& puzzle_part)
{
    std::fstream in{ filename };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::vector<std::vector<int>> report;
    std::string line;

    while (getline(in, line))
    {
        std::vector<int> history;
        std::istringstream iss{ line };
        std::string s;
        while (getline(iss, s, ' '))
        {
            history.push_back(std::stoi(s));
        }
        if (puzzle_part == PuzzlePart::two)
        {
            std::reverse(std::begin(history), std::end(history));
        }
        report.emplace_back(history);
    }

    return report;
}

int solve(const Report& report)
{
    int sum{ 0 };

    for (const auto& history : report)
    {
        std::vector<std::vector<int>> differences;
        differences.emplace_back(history);
        while (!std::all_of(std::cbegin(differences.back()), std::cend(differences.back()), [](const auto& i) {return i == 0; }))
        {
            std::vector<int> difference_sequence;

            // std::adjacent_difference looked promising, but it preserves the first element
            std::transform(std::cbegin(differences.back()), std::prev(std::cend(differences.back())), std::next(std::cbegin(differences.back())),
                std::back_inserter(difference_sequence), [](const auto& a, const auto& b) { return b - a; });

            differences.emplace_back(difference_sequence);
        }
        differences.back().push_back(0);
        for (auto row{ std::rbegin(differences) }; row != std::prev(std::rend(differences)); ++row)
        {
            auto prev_row{ std::next(row) };
            (*prev_row).push_back((*row).back() + (*prev_row).back());
        }
        sum += differences.front().back();
    }

    return sum;
}
