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

int part1(const std::vector<Game>& games);

int part2(const std::vector<Game>& games);
