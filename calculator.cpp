//Program Name: EECS 348 Lab 10
//Program Discription and Purpose: converting a string to a double and doing addition with it
//Input: provided by user as a file
//Output: formatted double and addition results
//Collaborators: no collaborators
//Sources: ChatGPT
//Author Name: Rund Al-kofahi
//Creation Date: 4/10/2025

#include "calculator.hpp"  // header file
#include <fstream>  // I/O
#include <cctype>  // to check charecters
#include <iostream>  // to standard input/stream
#include <sstream>  // string operations
#include <algorithm>  // for std::isspace and std::remove
#include <regex>  // for reqular expressions
#include <vector>  // for std::vector
#include <iomanip>  // to contol output formatting

// function to covert and parse a valid number to a double
double parse_number(const std::string &expression) {
    std::istringstream iss(expression);  // to create a string stream 
    double result;  // variable to store the parsed double
    iss >> result;  // extracting the double from the stream
    return result;  // returning the parsed number
}

// function to check if a string is a valid double
bool is_valid_double(const std::string &str) {  
    std::string trimmed = str;

    // removing whitespace at the begning
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

// a function to add two valid double strings
std::string add_doubles(const std::string &a, const std::string &b) {
    double num1 = parse_number(a);  // converting first string to a double
    double num2 = parse_number(b);  // converting second str to a double
    double sum = num1 + num2;  // adding them

    std::ostringstream out;  // creating an output str steam for results
    out << std::fixed << std::setprecision(10) << sum;  // format to 10 decimal places

    std::string result = out.str();  // to convert the output to a string

    // removing trailing zeroes
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    if (result.back() == '.') result.pop_back();  // and decimal points

    return result;  // to return the sum
}
