#pragma once

#include <fstream>
#include <string>
#include <vector>

using History = std::vector<int>;
using Report = std::vector<History>;

Report read_input(const std::string& filename);

int part1(const Report& report);
