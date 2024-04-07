#pragma once

#include <fstream>
#include <string>
#include <vector>

using Report = std::vector<std::vector<int>>;

Report read_input(const std::string& filename);

int part1(const Report& report);
