#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <sys/stat.h>

std::vector<std::string> ft_split(const std::string& str, const std::string& delim);
bool isThereSuchDir(std::string full_path);
bool isThereSuchFile(std::string full_path);

#endif