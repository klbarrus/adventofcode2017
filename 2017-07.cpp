// AdventOfCode 2017 Day 07

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>

struct puzz_node {
    std::string name;
    int weight;
    std::vector<std::string> child;
    int children_total_weight;
    bool balanced;

    puzz_node(std::string& n, int w): name{n}, weight{w}, child{}, children_total_weight{0}, balanced(false) {}

    void add_child(std::string& cn) {
        child.push_back(cn);
    }

    size_t num_children() const {
        return child.size();
    }
};
 int fill_out_weights(std::map<std::string, puzz_node>& nodes, const std::string& sv) {
    auto pn = nodes.at(sv);
    if (pn.num_children() == 0)
        return pn.weight;

    std::vector<int> weights;

    for (const auto& i : pn.child) {
        auto child_weight = fill_out_weights(nodes, i);
        weights.push_back(child_weight);
    }
    if (std::all_of(weights.begin(), weights.end(), [=](auto i){return i == weights[0];}))
        pn.balanced = true;
    pn.children_total_weight = std::accumulate(weights.begin(), weights.end(), 0);

    auto total = pn.weight + pn.children_total_weight;
    auto [it, ins] = nodes.insert_or_assign(sv, std::move(pn));

    return total;
 }

 void find_unbalanced_nodes(std::vector<std::string>& unbalanced, const std::map<std::string, puzz_node>& nodes, const std::string& sv) {
    auto pn = nodes.at(sv);
    if (!pn.balanced && pn.num_children() != 0)
        unbalanced.push_back(pn.name);

    for (const auto& i : pn.child)
        find_unbalanced_nodes(unbalanced, nodes, i);
 }

 struct balance_info {
     std::string name;
     int weight;
 };

 void balance_tree(const std::vector<std::string>& unbalanced, const std::map<std::string, puzz_node>& nodes) {
// the node that needs balancing is the highest one in the tree that is unbalanced
// i.e. the last node added to the list of unbalanced nodes

    auto pn = nodes.at(unbalanced[unbalanced.size()-1]);
    std::cout << "balancing " << pn.name << ": ";

    std::vector<balance_info> balnodes;

    for (const auto& i : pn.child) {
        auto cn = nodes.at(i);
        balnodes.push_back(balance_info{cn.name, cn.weight + cn.children_total_weight});
    }

    int min = balnodes[0].weight;
    int max = balnodes[0].weight;

    for (const auto& i : balnodes) {
        if (i.weight > max)
            max = i.weight;
        if (i.weight < min)
            min = i.weight;
    }

    int count_min = 0;
    int count_max = 0;

    for (const auto& i : balnodes) {
        if (i.weight == min)
            count_min++;
        if (i.weight == max)
            count_max++;
    }

    int delta = 0;
    std::string balance;

    for (const auto& i : balnodes) {
        if (count_min > count_max) {
// count_min is the mode; balance by subtracting from the node that weighs max
            if (i.weight == max) {
                delta = min - max;
                balance = i.name;
                std::cout << "subtract " << -delta << " from " << balance << "\n";
            }
        } else {
// count_max is the mode; balance by adding to the node that weight min
            if (i.weight == min) {
                delta = max - min;
                balance = i.name;
                std::cout << "add " << delta << " to " << balance << "\n";
            }
        }
    }

    auto bn = nodes.at(balance);
    std::cout << "new weight of " << balance << ": " << bn.weight + delta << "\n";
 }

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
    // add all names to a set for uniqueness, the remove names listed on the rhs

    std::set<std::string> names;
    std::regex towerInfo("(\\w+)");
    for (std::string& i: puzzle) {
        auto info_begin = std::sregex_iterator(i.begin(), i.end(), towerInfo);
        // 1st entry in each line is a tower name
        std::smatch m = *info_begin;
        names.insert(m.str());
    }

    for (std::string& i: puzzle) {
        auto info_begin = std::sregex_iterator(i.begin(), i.end(), towerInfo);
        auto info_end = std::sregex_iterator();
        // 3rd+ entry in each line are children/tower names
        auto info_third = info_begin;
        ++info_third;
        ++info_third;
        for (auto j = info_third; j != info_end; ++j) {
            std::smatch m = *j;
            names.erase(m.str());
        }
    }

    auto bottom = names.begin();
    std::cout << "part 1: " << *bottom << '\n';

    // for part 2, build a graph of nodes (using a std::map)
    //   1st pass, add node name, weight, children
    //   2nd pass, total up children weight for each node
    //   3rd pass, find wrong weight

    std::map<std::string, puzz_node> nodes;
    for (std::string& i: puzzle) {
        auto info_begin = std::sregex_iterator(i.begin(), i.end(), towerInfo);
        // 1st entry in line is name, 2nd entry is weight
        auto info_name = info_begin;
        auto info_weight = ++info_begin;
        std::string node_name = (*info_name).str();
        int node_weight = std::stoi((*info_weight).str());
        puzz_node pn = puzz_node(node_name, node_weight);
        // 3rd+ entry are children (if present)
        auto info_children = ++info_begin;
        auto info_end = std::sregex_iterator();
        for (auto j = info_children; j != info_end; ++j) {
            std::string child_name = (*j).str();
            pn.add_child(child_name);
        }
        nodes.try_emplace(node_name, std::move(pn));
    }

    fill_out_weights(nodes, *bottom);

    std::vector<std::string> unbalanced;
    find_unbalanced_nodes(unbalanced, nodes, *bottom);
    balance_tree(unbalanced, nodes);

    return 0;
}
