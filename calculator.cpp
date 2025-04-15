<<<<<<< HEAD
//Program Name: EECS 348 Lab 10 
=======
//Program Name: EECS 348 Lab 10
>>>>>>> fad0cff6bb3fabc4a2c99d325407d2c5c5086c4f
//Program Discription and Purpose: converting a string to a double and doing addition with it
//Input: provided by user as a file
//Output: formatted double and addition results
//Collaborators: no collaborators
//Sources: ChatGPT
//Author Name: Rund Al-kofahi
//Creation Date: 4/10/2025

#include "calculator.hpp"  // header file
#include <fstream>  // I/O
#include <cctype>  // to check characters
#include <iostream>  // to standard input/stream
#include <sstream>  // string operations
#include <algorithm>  // for std::isspace and std::remove
#include <regex>  // for regular expressions
#include <vector>  // for std::vector
#include <iomanip>  // to control output formatting

// function to convert and parse a valid number to a double
double parse_number(const std::string &expression) {
    std::istringstream iss(expression);  // to create a string stream 
    double result;  // variable to store the parsed double
    iss >> result;  // extracting the double from the stream
    return result;  // returning the parsed number
}

// function to check if a string is a valid double
bool is_valid_double(const std::string &str) {  
    std::string trimmed = str;

    // removing whitespace at the beginning
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // removing whitespace at the end
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), trimmed.end());

    // defining a regex pattern for a valid signed/unsigned double
    std::regex pattern(R"(^[+-]?[0-9]+(\.[0-9]+)?$)");
    return std::regex_match(trimmed, pattern);  // returning true if the string matches the regex pattern
}

// function to read a double string from a file
std::vector<std::string> read_numbers_from_file(const std::string &filename) {
    std::ifstream file(filename);  // opening the file for reading
    std::vector<std::string> numbers;  // a vector to store the doubles as strings
    std::string line;  // temporary string to hold each line

    // to read the file line by line:
    while (std::getline(file, line)) { 
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); // to clean the line
        if (!line.empty()) numbers.push_back(line);  // to only add non-empty lines to the vector
    }

    return numbers;  // returns the vector of the double string
}

// helper to remove leading zeros (used for comparing magnitudes)
std::string trim_leading_zeros(const std::string &s) {
    size_t i = 0;
    while (i < s.size() && s[i] == '0') ++i;
    return i == s.size() ? "0" : s.substr(i);
}

// helper function to split a double string into integer and fractional parts
std::pair<std::string, std::string> split_parts(const std::string &num) {
    size_t dot = num.find('.');
    if (dot == std::string::npos) return {num, "0"};
    return {num.substr(0, dot), num.substr(dot + 1)};
}

// helper function to compare two numeric strings as magnitudes
bool is_less_than(const std::string &a, const std::string &b) {
    auto [ai, af] = split_parts(a);
    auto [bi, bf] = split_parts(b);

    ai = trim_leading_zeros(ai);
    bi = trim_leading_zeros(bi);

    if (ai.size() != bi.size()) return ai.size() < bi.size();
    if (ai != bi) return ai < bi;

    while (af.size() < bf.size()) af += '0';
    while (bf.size() < af.size()) bf += '0';

    return af < bf;
}

// helper function to subtract smaller from larger (magnitude only)
std::string subtract_magnitudes(const std::string &larger, const std::string &smaller) {
    auto [int1, frac1] = split_parts(larger);
    auto [int2, frac2] = split_parts(smaller);

    // pad fractions
    while (frac1.size() < frac2.size()) frac1 += '0';
    while (frac2.size() < frac1.size()) frac2 += '0';

    // subtract fractional parts
    std::string frac_diff;
    int borrow = 0;
    for (int i = (int)frac1.size() - 1; i >= 0; i--) {
        int d1 = frac1[i] - '0' - borrow;
        int d2 = frac2[i] - '0';
        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        frac_diff = char((d1 - d2) + '0') + frac_diff;
    }

    // pad integers
    while (int1.size() < int2.size()) int1 = '0' + int1;
    while (int2.size() < int1.size()) int2 = '0' + int2;

    // subtract integer parts
    std::string int_diff;
    for (int i = (int)int1.size() - 1; i >= 0; i--) {
        int d1 = int1[i] - '0' - borrow;
        int d2 = int2[i] - '0';
        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        int_diff = char((d1 - d2) + '0') + int_diff;
    }

    int_diff = trim_leading_zeros(int_diff);
    while (!frac_diff.empty() && frac_diff.back() == '0') frac_diff.pop_back();

    return frac_diff.empty() ? int_diff + ".0" : int_diff + '.' + frac_diff;
}

// a function to add two valid double strings
std::string add_doubles(const std::string &a, const std::string &b) {
    int sign1 = 1, sign2 = 1;
    std::string sa = a, sb = b;

    if (sa[0] == '-') { sign1 = -1; sa = sa.substr(1); }
    else if (sa[0] == '+') { sa = sa.substr(1); }

    if (sb[0] == '-') { sign2 = -1; sb = sb.substr(1); }
    else if (sb[0] == '+') { sb = sb.substr(1); }

    // same sign = regular addition
    if (sign1 == sign2) {
        auto [int1, frac1] = split_parts(sa);
        auto [int2, frac2] = split_parts(sb);

        // pad fractions
        while (frac1.size() < frac2.size()) frac1 += '0';
        while (frac2.size() < frac1.size()) frac2 += '0';

        // add fractions
        std::string frac_sum;
        int carry = 0;
        for (int i = (int)frac1.size() - 1; i >= 0; i--) {
            int sum = (frac1[i] - '0') + (frac2[i] - '0') + carry;
            frac_sum = char(sum % 10 + '0') + frac_sum;
            carry = sum / 10;
        }

        // pad integers
        while (int1.size() < int2.size()) int1 = '0' + int1;
        while (int2.size() < int1.size()) int2 = '0' + int2;

        // add integers
        std::string int_sum;
        for (int i = (int)int1.size() - 1; i >= 0; i--) {
            int sum = (int1[i] - '0') + (int2[i] - '0') + carry;
            int_sum = char(sum % 10 + '0') + int_sum;
            carry = sum / 10;
        }
        if (carry) int_sum = '1' + int_sum;

        while (!frac_sum.empty() && frac_sum.back() == '0') frac_sum.pop_back();
        if (frac_sum.empty()) frac_sum = "0";

        if (sign1 == -1) int_sum = '-' + int_sum;
        return int_sum + '.' + frac_sum;
    }

    // opposite signs = subtraction
    bool a_greater = !is_less_than(sa, sb);
    std::string larger = a_greater ? sa : sb;
    std::string smaller = a_greater ? sb : sa;
    int result_sign = a_greater ? sign1 : sign2;

    std::string result = subtract_magnitudes(larger, smaller);
    if (result == "0.0") return result;
    return result_sign == -1 ? '-' + result : result;
}
