// AdventOfCode 2017 Day 02

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

int main(int argc, char* argv[]) {
    std::ifstream puzzle_in;
    if (argc > 1)
        puzzle_in.open(argv[1]);
    else
        puzzle_in.open("../2017-02.txt");

    int checksum1 = 0;
    int checksum2 = 0;
    std::string line;
    while (std::getline(puzzle_in, line)) {
        line = rtrim(line);
        int num;
        std::stringstream line_stream(line);
        std::vector<int> line_data;
        while (line_stream >> num)
            line_data.push_back(num);

        // line_data vector now contains the ints that were in the line string

        // find min and max for part 1 checksum
        auto [min_elem, max_elem] = std::minmax_element(line_data.begin(), line_data.end());
        checksum1 += (*max_elem - *min_elem);

        // generate combinations for part 2 checksum
        std::vector<bool> v(line_data.size());
        std::fill(v.begin(), v.begin() + 2, true);
        do {
            std::vector<int> combs;
            for (int i = 0; i < line_data.size(); ++i) {
                if (v[i]) {
                    combs.push_back(line_data[i]);
                }
            }

            // look for a pair that is evenly divisible
            if (combs[0] % combs[1] == 0) {
                checksum2 += (combs[0] / combs[1]);
                break;
            } else if (combs[1] % combs[0] == 0) {
                checksum2 += (combs[1] / combs[0]);
                break;
            }
        } while (std::prev_permutation(v.begin(), v.end()));
    }
    puzzle_in.close();

    std::cout << "part 1: " << checksum1 << '\n';
    std::cout << "part 2: " << checksum2 << '\n';

    return 0;
}
