#include "calculator.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    std::vector<std::string> numbers = read_numbers_from_file("test.txt");

    for (const std::string& number : numbers) {
        std::cout << "Input: " << number << "\n";
        if (is_valid_double(number)) {
            double parsed = parse_number(number);
            std::cout << "Valid. Parsed: " << parsed << "\n";

            std::string sum = add_doubles(number, "-123.456");
            std::cout << number << " + (-123.456) = " << sum << "\n";
        } else {
            std::cout << "Invalid double format.\n";
        }
        std::cout << "\n";
    }

    return 0;
}
