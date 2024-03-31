export module day06mod;

import std;

struct Race
{
    long long time;
    long long distance;
};

export std::vector<Race> read_input(const std::string& filename)
{
    std::fstream in{ std::fstream(filename) };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::vector<Race> races;

    std::string line;
    const std::regex number_r{ R"((\d+))" };
    std::smatch sm;

    // Get times
    getline(in, line);
    std::vector<long long> times;
    while (std::regex_search(line, sm, number_r))
    {
        times.push_back(std::stoll(sm[0]));
        line = sm.suffix();
    }

    // Get distances
    getline(in, line);
    std::vector<long long> distances;
    while (std::regex_search(line, sm, number_r))
    {
        distances.push_back(std::stoll(sm[0]));
        line = sm.suffix();
    }

    if (times.size() != distances.size())
    {
        throw std::invalid_argument("Bad input");
    }

    std::transform(std::cbegin(times), std::cend(times), std::cbegin(distances), std::back_inserter(races),
        [](const auto& t, const auto& d) { return Race{ t,d }; });

    return races;
}

export int part1(const std::vector<Race>& races)
{
    std::vector<long long> records;
    for (const auto& race : races)
    {
        std::vector<long long> results;
        for (auto speed{ 0 }; speed < race.time; ++speed)
        {
            auto time{ race.time - speed };
            auto result{ speed * time };
            results.push_back(result);
        }
        records.push_back(std::count_if(std::cbegin(results), std::cend(results), [=](int res) { return res > race.distance; }));
    }
    return std::accumulate(std::cbegin(records), std::cend(records), 1, std::multiplies());
}

export long long part2(const std::vector<Race>& races)
{
    // Per problem statement, concatenate race times and distances into a single race
    std::stringstream t_ss;
    std::stringstream d_ss;
    for (const auto& race : races)
    {
        t_ss << race.time;
        d_ss << race.distance;
    }
    auto t_str{ t_ss.str() };
    auto d_str{ d_ss.str() };

    Race race{ std::stoll(t_str),std::stoll(d_str)};

    std::vector<long long> results;
    for (auto speed{ 0 }; speed < race.time; ++speed)
    {
        auto time{ race.time - speed };
        auto result{ speed * time };
        results.push_back(result);
    }
    auto records = std::count_if(std::cbegin(results), std::cend(results), [=](const auto& res) { return res > race.distance; });

    return records;
}
