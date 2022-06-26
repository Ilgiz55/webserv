#include "utils2.hpp"

void exit_error(const std::string & error_message, int error_code)
{
	std::cerr << error_message << std::endl;
	exit(error_code);
}

std::string read_file(const std::string& f_name)
{

	std::ifstream ifs(f_name, std::ios::binary);

	std::string result;
	ifs.seekg(0, std::ios::end);
	try {
		result.resize(ifs.tellg());
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	ifs.seekg(0, std::ios::beg);
	ifs.read((char*)result.data(), result.size());
	ifs.close();
	return result;
}