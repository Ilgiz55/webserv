#ifndef CGI_HPP
# define CGI_HPP

#include <unistd.h>

# include "../webserv.hpp"
# include "../config/ConfigPars.hpp"
# include "../request.hpp"

class Cgi {
	public:
		Cgi() {}
		virtual ~Cgi() {}

		std::string		executeCgi(const std::string scriptName, Request &request, AConfig &conf);	// executes Cgi and returns body
	private:
		void		_setEnv(Request &request, AConfig &config);
		std::string	_body;
};

// ENV TO IMPLEMENT
// AUTH_TYPE
// CONTENT_LENGTH
// CONTENT_TYPE
// GATEWAY_INTERFACE
// PATH_INFO
// PATH_TRANSLATED
// QUERY_STRING˜

#endif
