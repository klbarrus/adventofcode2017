// AdventOfCode 2017 Day 01

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

int captcha(std::string& first, std::string& second) {
    int sum = 0;
    auto xi = first.begin();
    auto yi = second.begin();
    while (xi != first.end() && yi != second.end()) {
        if (*xi == *yi) {
            sum += int(*xi) - int('0');
        }
        *xi++;
        *yi++;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        fstream puzzle_f(argv[1], ios::in);
        ostringstream puzzle_s;
        puzzle_s << puzzle_f.rdbuf();
        string puzz_dig = puzzle_s.str();
        puzz_dig = rtrim(puzz_dig);
        puzzle_f.close();

        unsigned long len = puzz_dig.length();
        string puzz_one = puzz_dig;
        string puzz_two = puzz_dig;
        std::rotate(puzz_one.begin(), puzz_one.begin() + 1, puzz_one.end());
        std::rotate(puzz_two.begin(), puzz_two.begin() + len / 2, puzz_two.end());

        // compare original string (file contents) with rotated string(s), char by char,
        // and look for matches
        // doesn't seem to be a sequence-zip in c++ 17 yet

        cout << "part 1: " << captcha(puzz_dig, puzz_one) << "\n";
        cout << "part 2: " << captcha(puzz_dig, puzz_two) << "\n";
    }

    return 0;
}
