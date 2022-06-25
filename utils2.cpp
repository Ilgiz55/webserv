#include "utils2.hpp"

void exit_error(const std::string & error_message, int error_code)
{
	std::cerr << error_message << std::endl;
	exit(error_code);
}