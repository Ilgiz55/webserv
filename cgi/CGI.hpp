#ifndef CGI_HPP
# define CGI_HPP

# include "../webserv.hpp"
# include "../config/ConfigServer.hpp"
# include "../request.hpp"

class Cgi {
	public:
		std::string status;
		Cgi() {}
		virtual ~Cgi() {}

		std::string	executeCgi(const std::string scriptName, Request &request, AConfig &conf);	// executes Cgi and returns body
	private:
		void	setEnv(Request &request, const std::string scriptName);
};

// ENV TO IMPLEMENT
// AUTH_TYPE
// CONTENT_LENGTH
// CONTENT_TYPE
// GATEWAY_INTERFACE
// PATH_INFO
// PATH_TRANSLATED
// QUERY_STRING

#endif
