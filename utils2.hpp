#ifndef UTILS2_HPP
#define UTILS2_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

void exit_error(const std::string & error_message, int error_code);
std::string read_file(const std::string& f_name);
std::map<std::string, std::string> init_mime_types();
std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);

#endif