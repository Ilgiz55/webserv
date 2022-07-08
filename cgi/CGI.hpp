#ifndef CGI_HPP

# define CGI_HPP

# include "webserv.hpp"

# include "../config/ConfigPars.hpp"
# include "../request.hpp"

class Cgi {
	public:
		Cgi(Request &request, ConfigServer &config); // sets up env according to the request
		Cgi(Cgi const &src);
		virtual ~Cgi(void);

		Cgi   	&operator=(Cgi const &src);
		std::string		executeCgi(const std::string &scriptName);	// executes Cgi and returns body
	private:
		Cgi(void);
		void								_setEnv(Request &request, ConfigServer &config);
		char								**_getEnvAsCstrArray() const;
		int									_getSocket(unsigned int port);
		int									_connectSocket(unsigned int port);
		std::map<std::string, std::string>	_env;
		std::string							_body;
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
