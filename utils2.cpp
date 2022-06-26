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

std::map<std::string, std::string> init_mime_types()
{
    std::map<std::string, std::string> mt;

    mt.insert(std::make_pair("html","text/html"));
    mt.insert(std::make_pair("htm","text/html"));
    mt.insert(std::make_pair("shtml","text/html"));
    mt.insert(std::make_pair("css","text/css"));
    mt.insert(std::make_pair("xml","text/xml"));
    mt.insert(std::make_pair("gif","image/gif"));
    mt.insert(std::make_pair("jpeg","image/jpeg"));
    mt.insert(std::make_pair("jpg","image/jpeg"));
    mt.insert(std::make_pair("ico","image/x-icon"));
    // mt.insert(std::make_pair("",""));
    mt.insert(std::make_pair("application/octet-stream","bin"));
    // mt.insert(std::make_pair("",""));

    return mt;
}