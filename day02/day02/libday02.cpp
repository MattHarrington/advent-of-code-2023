#include <algorithm>
#include <fstream>
#include <regex>
#include <sstream>

#include "libday02.h"

std::vector<Game> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::vector<Game> games;
    const std::regex regex_game{ R"(Game (\d*): )" };
    const std::regex regex_red{ R"((\d*) red)" };
    const std::regex regex_green{ R"((\d*) green)" };
    const std::regex regex_blue{ R"((\d*) blue)" };

    std::string line;
    std::smatch sm;

    while (getline(in, line))
    {
        Game game;

        if (regex_search(line, sm, regex_game))
        {
            game.game_number = std::stoi(sm[1]);

            // Split string on semicolon
            // https://stackoverflow.com/a/10861816
            std::vector<std::string> revelations; // What the elf reveals each time
            std::stringstream ss{ sm.suffix() };
            while (ss.good())
            {
                std::string substr;
                getline(ss, substr, ';');
                revelations.push_back(substr);
            }

            // Process the revelations
            for (const auto& revelation : revelations)
            {
                if (regex_search(revelation, sm, regex_red))
                {
                    game.max_red = std::max(game.max_red, std::stoi(sm[1]));
                }
                if (regex_search(revelation, sm, regex_green))
                {
                    game.max_green = std::max(game.max_green, std::stoi(sm[1]));
                }
                if (regex_search(revelation, sm, regex_blue))
                {
                    game.max_blue = std::max(game.max_blue, std::stoi(sm[1]));
                }
            }
        }

        games.emplace_back(game);
    }

    return games;
}

int part1(const std::vector<Game>& games) noexcept
{
    const Game elf_criteria{ .max_red = 12, .max_green = 13, .max_blue = 14 };

    int sum_possible_game_numbers{ 0 };
    for (const auto& game : games)
    {
        if (game.max_red <= elf_criteria.max_red &&
            game.max_green <= elf_criteria.max_green &&
            game.max_blue <= elf_criteria.max_blue)
        {
            sum_possible_game_numbers += game.game_number;
        }
    }

    return sum_possible_game_numbers;
}

int part2(const std::vector<Game>& games) noexcept
{
    int sum_of_powers{ 0 };

    for (const auto& game : games)
    {
        const int power{ game.max_red * game.max_green * game.max_blue };
        sum_of_powers += power;
    }

    return sum_of_powers;
}
