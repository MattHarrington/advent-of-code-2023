#pragma once

#include <string>
#include <tuple>
#include <vector>

struct Game
{
    int game_number{ 0 };
    int max_red{ 0 };
    int max_green{ 0 };
    int max_blue{ 0 };
};

/// \brief Read an input file.
///
/// \return Vector of games.
std::vector<Game> read_input(
    const std::string& filename ///< The filename to read
);

/// \brief Solve part 1.
///
/// \return Sum of game numbers which meet the elf's criteria.
int part1(
    const std::vector<Game>& games ///< All of the games
) noexcept;

/// \brief Solve part 2.
///
/// \return Sum of powers of minumum number of cubes for each game.
int part2(
    const std::vector<Game>& games ///< All of the games
) noexcept;
