import std;
import day04mod;
#include <cassert>

int main()
{
    const auto sample_input{ read_input("sample_input.dat") };
    assert(6 == sample_input.size());
    assert(5 == sample_input.front().first.size());
    assert(8 == sample_input.front().second.size());

    const auto puzzle_input{ read_input("puzzle_input.dat") };
    assert(199 == puzzle_input.size());
    assert(10 == puzzle_input.front().first.size());
    assert(25 == puzzle_input.front().second.size());
}
