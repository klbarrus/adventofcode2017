// AdventOfCode 2017 Day 07

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

struct puzz_node {
    std::string name;
    int weight;
    std::vector<std::string> children;
    int children_weight;

    puzz_node(std::string& n, int w): name{n}, weight{w}, children{}, children_weight{0} {}

    void add_child(std::string& cn) {
        children.push_back(cn);
    }

    std::string get_name() const {
        return name;
    }

    int get_weight() const {
        return weight;
    }

    int get_num_children() const {
        return children.size();
    }
};

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
        // 1st entry in each line is a tower name
        std::smatch m = *info_begin;
        names.insert(m.str());
    }

    for (std::string& a: puzzle) {
        auto info_begin = std::sregex_iterator(a.begin(), a.end(), towerInfo);
        auto info_end = std::sregex_iterator();
        // 3rd+ entry in each line are children/tower names
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

    // for part 2, build a graph of nodes (using a std::map)
    // TODO: better graph would use boost's graph library (to figure out later)
    // 
    //   1st pass, add node name, weight, children
    //   2nd pass, total up children weight for each node
    //   3rd pass, find wrong weight

    std::map<std::string, puzz_node> nodes;
    for (std::string& a: puzzle) {
        auto info_begin = std::sregex_iterator(a.begin(), a.end(), towerInfo);
        // 1st entry in line is name, 2nd entry is weight
        auto info_name = info_begin;
        auto info_weight = ++info_begin;
        std::string node_name = (*info_name).str();
        int node_weight = std::stoi((*info_weight).str());
        puzz_node pn = puzz_node(node_name, node_weight);
        // 3rd+ entry are children (if present)
        auto info_children = ++info_begin;
        auto info_end = std::sregex_iterator();
        for (std::sregex_iterator i = info_children; i != info_end; ++i) {
            std::string child_name = (*i).str();
            pn.add_child(child_name);
        }
        nodes.try_emplace(node_name, std::move(pn));
    }

    for (auto const& [k, v]: nodes) {
        std::cout << v.get_name() << " (" << v.get_weight() << "), " << v.get_num_children() << "\n";
    }

    return 0;
}
