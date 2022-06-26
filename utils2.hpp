#ifndef UTILS2_HPP
#define UTILS2_HPP

#include <iostream>
#include <string>
#include <fstream>

void exit_error(const std::string & error_message, int error_code);
std::string read_file(const std::string& f_name);

#endif