#include "CGI.hpp"

Cgi::Cgi(Request &request, ConfigServer &config):
_body(request.getBody())
{
	this->_setEnv(request, config);
}

Cgi::Cgi(Cgi const &src) {
	if (this != &src) {
		this->_body = src._body;
		this->_env = src._env;
	}
	return ;
}

Cgi::~Cgi(void) {
	return ;
}

Cgi	&Cgi::operator=(Cgi const &src) {
	if (this != &src) {
		this->_body = src._body;
		this->_env = src._env;
	}
	return *this;
}

void		Cgi::_setEnv(Request &request, ConfigServer &config) {

	// setenv("CONTENT_LENGTH", std::to_string(_content_length).c_str(), 1); //  I'll think about that tomorrow.
	setenv("CONTENT_TYPE", "text/html", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("PATH_INFO", request.getUri().c_str(), 1);
	setenv("REQUEST_URI", request.getUri().c_str(), 1);
	setenv("QUERY_STRING", request.getQueryStr().c_str(), 1);
	setenv("REQUEST_METHOD", request.getMethod().c_str(), 1);
	setenv("REMOTE_ADDR", config.getListen().first.c_str(), 1);
	setenv("SCRIPT_NAME", "/Users/sfearow/.brew/bin/php-cgi", 1); //  I'll think about that tomorrow.
	setenv("SERVER_NAME", "webserv", 1);
	setenv("SERVER_PORT", std::to_string(config.getPort()).c_str(), 1);
	setenv("SERVER_PROTOCOL", request.getProtocol().c_str(), 1);
	setenv("SERVER_SOFTWARE", "WebServ/1.0", 1);
	setenv("AUTH_TYPE", "", 1);
	// setenv("PATH_TRANSLATED", _response_path.c_str(), 1); //  I'll think about that tomorrow.
	setenv("REMOTE_IDENT", "", 1);
	setenv("REMOTE_USER", "", 1);
	setenv("REDIRECT_STATUS", "200", 1);

	//  I'll think about that tomorrow.
	for (std::map<std::string, std::string>::iterator it = _requst_header.begin(), \
		it_end = _requst_header.end(); it != it_end; it++)
	{
		std::string tmp = it->first;
		for (int i = 0; i < tmp.size(); i++)
			tmp[i] = toupper(tmp[i]);
		setenv(("HTTP_" + tmp).c_str(), it->second.c_str(), 1);
	}
}

char	**Cgi::_getEnvAsCstrArray() const {
	char	**env = new char*[this->_env.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return env;
}

std::string	Cgi::executeCgi(const std::string& scriptName) {
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
	std::string	newBody;

	try {
		env = this->_getEnvAsCstrArray();
	}
	catch (std::bad_alloc &e) {
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	// SAVING STDIN AND STDOUT IN ORDER TO TURN THEM BACK TO NORMAL LATER
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	write(fdIn, _body.c_str(), _body.size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
	{
		std::cerr << RED << "Fork crashed." << RESET << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		char * const * nll = NULL;
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(scriptName.c_str(), nll, env);
		std::cerr << RED << "Execve crashed." << RESET << std::endl;
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buffer[CGI_BUFSIZE] = {0};
		waitpid(pid, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);
		ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, CGI_BUFSIZE);
			ret = read(fdOut, buffer, CGI_BUFSIZE - 1);
			newBody += buffer;
		}
	}

	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;

	if (!pid)
		exit(0);

	return (newBody);
}
