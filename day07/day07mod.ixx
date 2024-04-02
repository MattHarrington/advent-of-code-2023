export module day07mod;

import std;

enum class Card
{
	two = 2, three, four, five, six, seven,
	eight, nine, T, J, Q, K, A
};

enum class Type
{
	high_card, pair, two_pair, three_of_a_kind, full_house, four_of_a_kind, five_of_a_kind
};

Type get_type(const std::vector<Card>& cards)
{
	Type type{};
	std::map<Card, int> card_map;
	for (const auto& card : cards)
	{
		++card_map[card];
	}

	if (std::find_if(std::cbegin(card_map), std::cend(card_map),
		[](const auto& e) {return e.second == 5; }) != std::cend(card_map))
	{
		type = Type::five_of_a_kind;
	}
	else if (std::find_if(std::cbegin(card_map), std::cend(card_map),
		[](const auto& e) {return e.second == 4; }) != std::cend(card_map))
	{
		type = Type::four_of_a_kind;
	}
	else if (std::find_if(std::cbegin(card_map), std::cend(card_map),
		[](const auto& e) {return e.second == 3; }) != std::cend(card_map) &&
		std::find_if(std::cbegin(card_map), std::cend(card_map),
			[](const auto& e) {return e.second == 2; }) != std::cend(card_map))
	{
		type = Type::full_house;
	}
	else if (card_map.size() == 3 &&
		std::find_if(std::cbegin(card_map), std::cend(card_map),
			[](const auto& e) {return e.second == 3; }) != std::cend(card_map))
	{
		type = Type::three_of_a_kind;
	}
	else if (card_map.size() == 3 &&
		std::find_if(std::cbegin(card_map), std::cend(card_map),
			[](const auto& e) {return e.second == 2; }) != std::cend(card_map))
	{
		type = Type::two_pair;
	}
	else if (card_map.size() == 4 &&
		std::find_if(std::cbegin(card_map), std::cend(card_map),
			[](const auto& e) {return e.second == 2; }) != std::cend(card_map))
	{
		type = Type::pair;
	}
	else
	{
		type = Type::high_card;
	}
	return type;
}

struct Hand
{
	std::vector<Card> cards;
	int bid;
	friend bool operator<(const Hand& left, const Hand& right) {
		const auto this_type{ get_type(left.cards) };
		const auto other_type{ get_type(right.cards) };
		if (this_type != other_type)
		{
			return this_type < other_type;
		}
		else
		{
			for (auto i{ 0 }; i < left.cards.size(); ++i)
			{
				if (left.cards.at(i) == right.cards.at(i))
				{
					continue;
				}
				return left.cards.at(i) < right.cards.at(i);
			}
		}
	}
};

export std::vector<Hand> read_input(const std::string& filename)
{
	std::fstream in{ std::fstream(filename) };
	if (!in)
	{
		throw std::runtime_error("File not found");
	}

	std::vector<Hand> hands;
	std::string line;
	std::regex r{ R"(([AKQJT98765432]+) (\d+))" };
	std::smatch sm;

	while (getline(in, line))
	{
		if (std::regex_match(line, sm, r))
		{
			Hand hand;
			for (const auto& c : sm[1].str())
			{
				Card card;
				switch (c)
				{
				case '2':
					card = Card::two;
					break;
				case '3':
					card = Card::three;
					break;
				case '4':
					card = Card::four;
					break;
				case '5':
					card = Card::five;
					break;
				case '6':
					card = Card::six;
					break;
				case '7':
					card = Card::seven;
					break;
				case '8':
					card = Card::eight;
					break;
				case '9':
					card = Card::nine;
					break;
				case 'T':
					card = Card::T;
					break;
				case 'J':
					card = Card::J;
					break;
				case 'Q':
					card = Card::Q;
					break;
				case 'K':
					card = Card::K;
					break;
				case 'A':
					card = Card::A;
					break;
				default:
					throw std::invalid_argument("Invalid argument");
				}
				hand.cards.push_back(card);
			}
			hand.bid = std::stoi(sm[2]);
			hands.emplace_back(hand);
		}
	}

	return hands;
}



export long long part1(std::vector<Hand> hands)
{
	std::sort(std::begin(hands), std::end(hands));
	for (const auto& hand : hands)
	{
		std::stringstream ss;
		for (const auto& card : hand.cards)
		{
			char c;
			switch (card)
			{
			case Card::two:
				c = '2';
				break;
			case Card::three:
				c = '3';
				break;
			case Card::four:
				c = '4';
				break;
			case Card::five:
				c = '5';
				break;
			case Card::six:
				c = '6';
				break;
			case Card::seven:
				c = '7';
				break;
			case Card::eight:
				c = '8';
				break;
			case Card::nine:
				c = '9';
				break;
			case Card::T:
				c = 'T';
				break;
			case Card::J:
				c = 'J';
				break;
			case Card::Q:
				c = 'Q';
				break;
			case Card::K:
				c = 'K';
				break;
			case Card::A:
				c = 'A';
				break;
			default:
				throw std::invalid_argument("Bad input");
			}
			ss << c;
		}
		auto type{ get_type(hand.cards) };
		std::string type_s;
		switch (type)
		{
		case Type::five_of_a_kind:
			type_s = "five_of_a_kind";
			break;
		case Type::four_of_a_kind:
			type_s = "four_of_a_kind";
			break;
		case Type::full_house:
			type_s = "full_house";
			break;
		case Type::three_of_a_kind:
			type_s = "three_of_a_kind";
			break;
		case Type::two_pair:
			type_s = "two_pair";
			break;
		case Type::pair:
			type_s = "pair";
			break;
		case Type::high_card:
			type_s = "high_card";
			break;
		default:
			throw std::invalid_argument("Bad input");
		}
		println("Cards: {}, Type: {}", ss.str(), type_s);
	}
	long long winnings{ 0 };

	for (auto i{ 0 }; i < hands.size(); ++i)
	{
		winnings += hands.at(i).bid * (i + 1);
	}

	return winnings;
}
