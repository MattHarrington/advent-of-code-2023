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

    }

    return sum;
}
