// AdventOfCode 2017 Day 06

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    std::ifstream puzzle_in;
    if (argc > 1)
        puzzle_in.open(argv[1]);
    else
        puzzle_in.open("../2017-06.txt");

    std::vector<unsigned int> blocks;
    std::vector<std::vector<unsigned int>> state;
    unsigned int a;
    while (puzzle_in >> a)
        blocks.push_back(a);
    puzzle_in.close();

    unsigned int cycles = 0;
    bool seenBefore = false;
    while (!seenBefore) {
        // find redistribution block
        auto max = std::max_element(blocks.begin(), blocks.end());
        auto index = max - blocks.begin();

        // redistribute
        unsigned int count = blocks[index];
        blocks[index] = 0;

        // circularly add blocks
        cycles++;
        while (count > 0) {
            index = (index + 1) % blocks.size();
            blocks[index] += 1;
            count--;
        }

        // see if state has been previously seen
        // if not, save state
        auto it = std::find(state.begin(), state.end(), blocks);
        if (it != state.end()) {
            seenBefore = true;
            auto dist = std::distance(it, state.end());

            std::cout << "part 1: " << cycles << '\n';
            std::cout << "part 2: " << dist << '\n';
        } else {
            state.push_back(blocks);
        }
    }


    return 0;
}
