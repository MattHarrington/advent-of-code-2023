#pragma once

#include <string>
#include <vector>

std::vector<std::string> read_input(
    const std::string& filename
);

int part1(
    const std::vector<std::string>& schematic
);
