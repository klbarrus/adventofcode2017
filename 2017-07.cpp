// AdventOfCode 2017 Day 07

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::ifstream puzzle_in;
    if (argc > 1)
        puzzle_in.open(argv[1]);
    else
        puzzle_in.open("../2017-07.txt");
    std::string line;
    std::vector<std::string> puzzle;
    while (std::getline(puzzle_in, line))
        puzzle.push_back(line);
    puzzle_in.close();

    // for part 1, the base tower will be the only one not listed on the rhs
    // add all names to a set for uniqeness, the remove names listed on the rhs

    std::set<std::string> names;
    std::regex towerInfo("(\\w+)");
    for (std::string& a: puzzle) {
        auto info_begin = std::sregex_iterator(a.begin(), a.end(), towerInfo);
        // first entry in each line is a tower name
        std::smatch m = *info_begin;
        names.insert(m.str());
    }

    for (std::string& a: puzzle) {
        auto info_begin = std::sregex_iterator(a.begin(), a.end(), towerInfo);
        auto info_end = std::sregex_iterator();
        // 3rd+ entry in each line are tower names
        auto info_third = info_begin;
        ++info_third;
        ++info_third;
        for (std::sregex_iterator i = info_third; i != info_end; ++i) {
            std::smatch m = *i;
            names.erase(m.str());
        }
    }

    auto tower = names.begin();
    std::cout << "part 1: " << *tower << '\n';

    return 0;
}
