export module day05mod;

import std;

class Almanac
{
public:
    Almanac(std::vector<long long> s, std::vector<std::vector<long long>> ssr,
        std::vector<std::vector<long long>> sfr, std::vector<std::vector<long long>> fwr,
        std::vector<std::vector<long long>> wlr, std::vector<std::vector<long long>> ltr,
        std::vector<std::vector<long long>> thr, std::vector<std::vector<long long>> hlr) :
        seeds(s), seed_to_soil_ranges(ssr), soil_to_fertilizer_ranges(sfr),
        fertilizer_to_water_ranges(fwr), water_to_light_ranges(wlr), light_to_temperature_ranges(ltr),
        temperature_to_humidity_ranges(thr), humidity_to_location_ranges(hlr)
    {}
    std::vector<long long> seeds;
    std::vector<std::vector<long long>> seed_to_soil_ranges;
    std::vector<std::vector<long long>> soil_to_fertilizer_ranges;
    std::vector<std::vector<long long>> fertilizer_to_water_ranges;
    std::vector<std::vector<long long>> water_to_light_ranges;
    std::vector<std::vector<long long>> light_to_temperature_ranges;
    std::vector<std::vector<long long>> temperature_to_humidity_ranges;
    std::vector<std::vector<long long>> humidity_to_location_ranges;
};

std::vector<std::vector<long long>> get_ranges(std::fstream& in)
{
    std::vector<std::vector <long long>> ranges;
    std::string line;
    getline(in, line);
    const std::regex entry_r{ R"((\d+) (\d+) (\d+))" };
    std::smatch sm;
    while (std::regex_match(line, sm, entry_r))
    {
        auto destination_range_start{ std::stoll(sm[1]) };
        auto source_range_start{ std::stoll(sm[2]) };
        auto range_length{ std::stoll(sm[3]) };
        std::vector<long long> range = { destination_range_start, source_range_start, range_length };
        ranges.emplace_back(range);
        getline(in, line); // Next line
    }
    return ranges;
}

export Almanac read_input(const std::string& filename)
{
    std::fstream in{ std::fstream(filename) };
    if (!in)
    {
        throw std::runtime_error("File not found");
    }

    std::string line;
    const std::regex number_r{ R"((\d+))" };
    std::smatch sm;

    // Get seeds
    getline(in, line);
    std::vector<long long> seeds;
    while (std::regex_search(line, sm, number_r))
    {
        seeds.push_back(std::stoll(sm[0]));
        line = sm.suffix();
    }

    getline(in, line);
    getline(in, line);

    // Get ranges
    auto seed_to_soil_ranges = get_ranges(in);
    getline(in, line);
    auto soil_to_fertilizer_ranges = get_ranges(in);
    getline(in, line);
    auto fertilizer_to_water_ranges = get_ranges(in);
    getline(in, line);
    auto water_to_light_ranges = get_ranges(in);
    getline(in, line);
    auto light_to_temperature_ranges = get_ranges(in);
    getline(in, line);
    auto temperature_to_humidity_ranges = get_ranges(in);
    getline(in, line);
    auto humidity_to_location_ranges = get_ranges(in);

    Almanac almanac{ seeds, seed_to_soil_ranges, soil_to_fertilizer_ranges,
        fertilizer_to_water_ranges, water_to_light_ranges, light_to_temperature_ranges,
        temperature_to_humidity_ranges, humidity_to_location_ranges };

    return almanac;
}

// Map a source to a destination using provided ranges
long long map(long long source, const std::vector <std::vector<long long>>& ranges)
{
    for (const auto& range : ranges)
    {
        auto destination_range_start{ range.at(0) };
        auto source_range_start{ range.at(1) };
        auto range_length{ range.at(2) };
        if (source >= source_range_start && source <= source_range_start + range_length)
        {
            source = destination_range_start + source - source_range_start;
            break;
        }
    }

    return source;
}

export long long part1(const Almanac& almanac)
{
    auto lowest_location{ std::numeric_limits<long long>::max() };
    for (const auto& seed : almanac.seeds)
    {
        const auto soil{ map(seed, almanac.seed_to_soil_ranges) };
        const auto fertilizer{ map(soil, almanac.soil_to_fertilizer_ranges) };
        const auto water{ map(fertilizer, almanac.fertilizer_to_water_ranges) };
        const auto light{ map(water, almanac.water_to_light_ranges) };
        const auto temperature{ map(light, almanac.light_to_temperature_ranges) };
        const auto humidity{ map(temperature, almanac.temperature_to_humidity_ranges) };
        const auto location{ map(humidity, almanac.humidity_to_location_ranges) };
        lowest_location = std::min(lowest_location, location);
    }
    return lowest_location;
}

export long long part2(const Almanac& almanac)
{
    auto lowest_location{ std::numeric_limits<long long>::max()};
    for (auto it{ std::cbegin(almanac.seeds) }; it != std::cend(almanac.seeds); it += 2)
    {
        const auto starting_seed{ *it };
        const auto length_of_range{ *std::next(it) };
        for (auto seed{ starting_seed }; seed <= starting_seed + length_of_range; ++seed)
        {
            const auto soil{ map(seed, almanac.seed_to_soil_ranges) };
            const auto fertilizer{ map(soil, almanac.soil_to_fertilizer_ranges) };
            const auto water{ map(fertilizer, almanac.fertilizer_to_water_ranges) };
            const auto light{ map(water, almanac.water_to_light_ranges) };
            const auto temperature{ map(light, almanac.light_to_temperature_ranges) };
            const auto humidity{ map(temperature, almanac.temperature_to_humidity_ranges) };
            const auto location{ map(humidity, almanac.humidity_to_location_ranges) };
            lowest_location = std::min(lowest_location, location);
        }
    }
    return lowest_location;
}
