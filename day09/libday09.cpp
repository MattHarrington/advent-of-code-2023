#include <algorithm>
#include <sstream>

#include "libday09.hpp"

Report read_input(const std::string& filename)
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
        report.emplace_back(history);
    }

    return report;
}

int part1(const Report& report)
{
    int sum{ 0 };

    for (const auto& history : report)
    {
        std::vector<std::vector<int>> pyramid;
        pyramid.emplace_back(history);
        while (!std::all_of(std::cbegin(pyramid.back()), std::cend(pyramid.back()), [](const auto& i) {return i == 0; }))
        {
            std::vector<int> differences;
            std::transform(std::cbegin(pyramid.back()), std::prev(std::cend(pyramid.back())), std::next(std::cbegin(pyramid.back())),
                std::back_inserter(differences), [](const auto& a, const auto& b) { return b - a; });
            pyramid.emplace_back(differences);
        }
        pyramid.back().push_back(0);
        for (auto row{ std::rbegin(pyramid) }; row != std::prev(std::rend(pyramid)); ++row)
        {
            auto prev_row{ std::next(row) };
            (*prev_row).push_back((*row).back() + (*prev_row).back());
        }
        sum += pyramid.front().back();
    }

    return sum;
}
