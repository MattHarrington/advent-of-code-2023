export module day04mod;

import std;

export std::vector<std::pair<std::vector<int>, std::vector<int>>> read_input(const std::string& filename)
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
