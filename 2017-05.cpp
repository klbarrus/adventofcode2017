// AdventOfCode 2017 Day 05

#include <fstream>
#include <iostream>
#include <vector>

unsigned int do_jumps(std::vector<int>& table, int (* fn)(int)) {
    unsigned int pos = 0;
    unsigned int count = 0;
    while (pos < table.size()) {
        int offset = table[pos];
        table[pos] += fn(offset);
        pos += offset;
        count++;
    }
    return count;
}

int calc_off1(int off) {
    return 1;
}

int calc_off2(int off) {
    if (off >= 3)
        return -1;
    else
        return 1;
}

int main(int argc, char* argv[]) {
    std::ifstream puzzle_in;
    if (argc > 1)
        puzzle_in.open(argv[1]);
    else
        puzzle_in.open("../2017-05.txt");

    std::vector<int> jumps;
    int a;
    while (puzzle_in >> a)
        jumps.push_back(a);
    puzzle_in.close();

    std::vector<int> jumps2(jumps);

    std::cout << "part 1: " << do_jumps(jumps, calc_off1) << '\n';
    std::cout << "part 2: " << do_jumps(jumps2, calc_off2) << '\n';
    return 0;
}
