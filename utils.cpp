#include "utils.hpp"

std::vector<std::string> ft_split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos;
	do {
		pos = str.find(delim, prev);
		if (pos == std::string::npos)
			pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty())
			tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

bool isThereSuchDir(std::string full_path) {
	struct stat s;
	if( stat(full_path.c_str(),&s) == 0 )
	{
		if( s.st_mode & S_IFDIR )
			return true;
	}
	return false;
}

bool isThereSuchFile(std::string full_path) {
	struct stat s;
	if( stat(full_path.c_str(),&s) == 0 )
	{
		if( s.st_mode & S_IFREG )
			return true;
	}
	return false;
}