#pragma once

#include <map>
#include <string>
#include <utility>

struct Map
{
	std::string instructions;
	std::map<std::string, std::pair<std::string, std::string>> network;
};

Map read_input(const std::string&);

int part1(const Map&);
