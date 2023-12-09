#pragma once

#include <string>
#include <vector>

/// \brief Read an input file.
///
/// \return Vector of lines in the engine schematic.
std::vector<std::string> read_input(
    const std::string& filename ///< The filename to read
);

/// \brief Solve part 1.
///
/// \return Sum of all part numbers.
int part1(
    const std::vector<std::string>& schematic ///< The engine schematic
);

/// \brief Solve part 2.
///
/// \return Sum of all gear ratios.
int part2(
    const std::vector<std::string>& schematic ///< The engine schematic
);
