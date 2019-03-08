// AdventOfCode 2017 Day 01

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        fstream puzz(argv[1], ios::in);
        ostringstream puzz_s;
        puzz_s << puzz.rdbuf();
        string puzz_digits = puzz_s.str();
        puzz_digits = rtrim(puzz_digits);
        puzz.close();

        int sum{0};
        char prev{0};

        for (char& digit : puzz_digits) {
            if (digit == prev) {
                sum += int(prev) - int('0');
            }
            prev = digit;
        }

        char first = puzz_digits[0];
        char last = puzz_digits.back();

        if (first == last) {
            sum += int(first) - int('0');
        }

        cout << "part 1: " << sum << "\n";

        unsigned long digits_len = puzz_digits.length();
        sum = 0;

        for (unsigned long i = 0; i < digits_len; ++i) {
            char curr = puzz_digits[i];
            char circle = puzz_digits[(i + digits_len / 2) % digits_len];
            if (curr == circle) {
                sum += int(curr) - int('0');
            }
        }

        cout << "part 2: " << sum << "\n";
    }

    return 0;
}
