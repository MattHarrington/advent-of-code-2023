#pragma once

#include <string>
#include <vector>

/// \brief Read an input file.
///
/// \return Vector of calibration values for the trebuchet.
std::vector<std::string> read_input(
    const std::string& filename ///< The filename to read
);

/// \brief Solve part 1.
///
/// \return Sum of calibration values.
int part1(
    const std::vector<std::string>& ///< Vector of calibration values
);

/// \brief Solve part 2.
///
/// \return Sum of calibration values.
int part2(
    const std::vector<std::string>& ///< Vector of calibration values
);
