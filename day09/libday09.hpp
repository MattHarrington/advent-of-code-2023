#pragma once

#include <fstream>
#include <string>
#include <vector>

using History = std::vector<int>;
using Report = std::vector<History>;

enum class PuzzlePart
{
    one, two
};

Report read_input(const std::string& filename, const PuzzlePart& puzzle_part);

int solve(const Report& report);
