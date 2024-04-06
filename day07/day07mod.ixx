export module day07mod;

import std;

export enum class PuzzlePart
{
	one, two
};

enum class Card
{
	Joker = 1, Two, Three, Four, Five, Six, Seven,
	Eight, Nine, Ten, Jack, Queen, King, Ace
};

enum class Type
{
	high_card, pair, two_pair, three_of_a_kind, full_house, four_of_a_kind, five_of_a_kind
};

Type get_type(const std::vector<Card>& cards, const PuzzlePart& puzzle_part)
{
	Type type{};
	std::map<Card, int> card_map;
	for (const auto& card : cards)
	{
		++card_map[card];
	}

	if (puzzle_part == PuzzlePart::two)
	{
		const auto num_jokers{ card_map[Card::Joker] };
		card_map.erase(Card::Joker);
		auto max_card_it{ std::max_element(std::cbegin(card_map), std::cend(card_map), [](const auto& a, const auto& b) { return a.second < b.second; }) };
		if (max_card_it == std::cend(card_map))
		{
			// Hand was all Jokers. Treat it as 5 Aces.
			card_map[Card::Ace] += num_jokers;
		}
		else
		{
			card_map[(*max_card_it).first] += num_jokers;
		}
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
	PuzzlePart puzzle_part;
	friend bool operator<(const Hand& left, const Hand& right) {
		const auto this_type{ get_type(left.cards, left.puzzle_part) };
		const auto other_type{ get_type(right.cards, right.puzzle_part) };
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
			return false; // Hands are equal. Does not occur in this puzzle.
		}
	}
};

export std::vector<Hand> read_input(const std::string& filename, const PuzzlePart& puzzle_part = PuzzlePart::one)
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
					card = Card::Two;
					break;
				case '3':
					card = Card::Three;
					break;
				case '4':
					card = Card::Four;
					break;
				case '5':
					card = Card::Five;
					break;
				case '6':
					card = Card::Six;
					break;
				case '7':
					card = Card::Seven;
					break;
				case '8':
					card = Card::Eight;
					break;
				case '9':
					card = Card::Nine;
					break;
				case 'T':
					card = Card::Ten;
					break;
				case 'J':
					puzzle_part == PuzzlePart::one ? card = Card::Jack : card = Card::Joker;
					break;
				case 'Q':
					card = Card::Queen;
					break;
				case 'K':
					card = Card::King;
					break;
				case 'A':
					card = Card::Ace;
					break;
				default:
					throw std::invalid_argument("Invalid argument");
				}
				hand.cards.push_back(card);
			}
			hand.bid = std::stoi(sm[2]);
			hand.puzzle_part = puzzle_part;
			hands.emplace_back(hand);
		}
	}

	return hands;
}

void print_hands(const std::vector<Hand>& hands)
{
	for (const auto& hand : hands)
	{
		std::stringstream ss;
		for (const auto& card : hand.cards)
		{
			char c;
			switch (card)
			{
			case Card::Joker:
				c = '*';
				break;
			case Card::Two:
				c = '2';
				break;
			case Card::Three:
				c = '3';
				break;
			case Card::Four:
				c = '4';
				break;
			case Card::Five:
				c = '5';
				break;
			case Card::Six:
				c = '6';
				break;
			case Card::Seven:
				c = '7';
				break;
			case Card::Eight:
				c = '8';
				break;
			case Card::Nine:
				c = '9';
				break;
			case Card::Ten:
				c = 'T';
				break;
			case Card::Jack:
				c = 'J';
				break;
			case Card::Queen:
				c = 'Q';
				break;
			case Card::King:
				c = 'K';
				break;
			case Card::Ace:
				c = 'A';
				break;
			default:
				throw std::invalid_argument("Bad input");
			}
			ss << c;
		}
		auto type{ get_type(hand.cards, hand.puzzle_part) };
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
		println("Cards: {}, Type: {}, Bid: {}", ss.str(), type_s, hand.bid);
	}
}

export int get_score(std::vector<Hand> hands)
{
	std::sort(std::begin(hands), std::end(hands));

#ifdef _DEBUG
	print_hands(hands);
#endif

	auto winnings{ 0 };
	for (auto i{ 0 }; i < hands.size(); ++i)
	{
		winnings += hands.at(i).bid * (i + 1);
	}

	return winnings;
}
