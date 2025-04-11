#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>
#include <vector>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);  // expects a validated double-format string, returns its value as a double

bool is_valid_double(const std::string &expression);
std::vector<std::string> read_numbers_from_file(const std::string &filename);
std::string add_doubles(const std::string &a, const std::string &b);
std::string multiply_doubles(const std::string &a, const std::string &b);

#endif // __CALCULATOR_HPP
