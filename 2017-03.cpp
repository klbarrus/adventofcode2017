// AdventOfCode 2017 Day 03

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        unsigned int start;
        std::fstream puzzle_in(argv[1]);
        puzzle_in >> start;
        puzzle_in.close();

        unsigned int res = 0;
        unsigned int oddsq = 3;
        while (oddsq * oddsq < start)
            oddsq += 2;

        unsigned int fs = (oddsq * oddsq - start) % (oddsq - 1);
        if (fs > (oddsq - 1) / 2)
            res = fs;
        else
            res = oddsq - 1 - fs;

        std::cout << "part 1: " << res << '\n';

	// for part 2, see OEIS sequence 141481 (https://oeis.org/A141481)
    }

    return 0;
}
