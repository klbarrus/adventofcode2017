// AdventOfCode 2017 Day 04

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

std::string& rtrim(std::string& str, const std::string& chars = "\t\r\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        int total_1 = 0;
        int total_2 = 0;
        std::ifstream puzzle_in(argv[1]);
        std::string line;

        while (std::getline(puzzle_in, line)) {
            line = rtrim(line);
            std::string word;
            std::stringstream line_stream(line);
            std::vector<std::string> line_data;

            while (line_stream >> word) {
                line_data.push_back(word);
            }

            bool valid_1 = true;
            bool valid_2 = true;
            std::set<std::string> pass_1;
            std::set<std::string> pass_2;
            std::pair<std::set<std::string>::iterator, bool> res_1;
            std::pair<std::set<std::string>::iterator, bool> res_2;

            // part1 = insert words into a set; duplicates are invalid
            // part2 = sort letters of the words before inserting into set; duplicates are invalid
            for (std::string& word : line_data) {
                res_1 = pass_1.insert(word);
                if (!res_1.second)
                    valid_1 = false;

                std::sort(word.begin(), word.end());
                res_2 = pass_2.insert(word);
                if (!res_2.second)
                    valid_2 = false;
            }

            if (valid_1)
                total_1++;
            if (valid_2)
                total_2++;
        }
        
        puzzle_in.close();

        std::cout << "part 1: " << total_1 << '\n';
        std::cout << "part 2: " << total_2 << '\n';
    }

    return 0;
}
