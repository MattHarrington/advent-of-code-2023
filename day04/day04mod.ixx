export module day04mod;

import std;

using scratchcard = std::pair<std::vector<int>, std::vector<int>>;

export std::vector<scratchcard> read_input(const std::string& filename)
{
    std::vector <std::pair<std::vector<int>, std::vector<int>>> scratchcards;

    std::fstream in{ std::fstream(filename) };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::string line;
    const std::regex r{ R"(Card[\d ]+: ([\d ]+) \| ([\d ]+))" };
    std::smatch sm;

    while (getline(in, line))
    {
        if (std::regex_match(line, sm, r))
        {
            auto winning_numbers_s{ sm[1] };
            std::vector<int> winning_numbers;
            auto my_numbers_s{ sm[2] };
            std::vector<int> my_numbers;

            // Split string https://stackoverflow.com/a/10861816
            std::stringstream winning_numbers_ss{ winning_numbers_s };
            while (winning_numbers_ss.good())
            {
                std::string winning_number_s;
                getline(winning_numbers_ss, winning_number_s, ' ');
                if (!winning_number_s.empty())
                {
                    winning_numbers.push_back(std::stoi(winning_number_s));
                }
            }
            std::stringstream my_numbers_ss{ my_numbers_s };
            while (my_numbers_ss.good())
            {
                std::string my_number_s;
                getline(my_numbers_ss, my_number_s, ' ');
                if (!my_number_s.empty())
                {
                    my_numbers.push_back(std::stoi(my_number_s));
                }
            }
            scratchcards.emplace_back(std::make_pair(winning_numbers, my_numbers));
        }
    }

    return scratchcards;
}

static int get_number_of_matches(const scratchcard& scratchcard)
{
    int matches{ 0 };
    const auto [winning_numbers, my_numbers] {scratchcard};
    for (const auto& number : my_numbers)
    {
        if (std::find(std::cbegin(winning_numbers), std::cend(winning_numbers), number) != std::cend(winning_numbers))
        {
            ++matches;
        }
    }
    return matches;
}

export int part1(const std::vector<scratchcard>& scratchcards)
{
    auto total_points{ 0.0 };

    for (const auto& scratchcard : scratchcards)
    {
        const auto matches{ get_number_of_matches(scratchcard) };
        if (matches > 0)
        {
            total_points += std::pow(2, matches - 1);
        }
    }

    return static_cast<int>(total_points);
}

export int part2(const std::vector<scratchcard>& scratchcards)
{
    std::vector<int> card_counts(scratchcards.size(), 1);

    for (size_t card_number{ 0 }; card_number < scratchcards.size(); ++card_number)
    {
        for (size_t j{ 0 }; j < card_counts.at(card_number); ++j)
        {
            const auto matches{ get_number_of_matches(scratchcards.at(card_number)) };
            for (auto k{ 1 }; k < matches + 1; ++k)
            {
                ++card_counts.at(card_number + k);
            }
        }
    }

    const auto total_cards{ std::accumulate(std::cbegin(card_counts), std::cend(card_counts), 0) };
    return total_cards;
}
