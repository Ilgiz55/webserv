#ifndef UTILS2_HPP
#define UTILS2_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
# include <sstream>
# include <sys/types.h>
# include <sys/stat.h>

void exit_error(const std::string & error_message, int error_code);
std::string read_file(const std::string& f_name);
std::map<std::string, std::string> init_mime_types();
std::string ft_ltrim(const std::string &s);
std::string ft_rtrim(const std::string &s);
std::string ft_trim(const std::string &s);
// std::vector<std::string> _split(const std::string &str, const std::string &delim);

#endif