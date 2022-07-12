#include "CGI.hpp"

void Cgi::setEnv(Request &request, AConfig &config) {

	// setenv("CONTENT_LENGTH", std::to_string(_content_length).c_str(), 1); //  I'll think about that tomorrow.
	setenv("CONTENT_TYPE", "text/html", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("PATH_INFO", request.getUri().c_str(), 1);
	setenv("REQUEST_URI", request.getUri().c_str(), 1);
	setenv("QUERY_STRING", request.getQueryStr().c_str(), 1);
	setenv("REQUEST_METHOD", request.getMethod().c_str(), 1);
	// setenv("REMOTE_ADDR", "127.0.0.1", 1); //  I'll think about that tomorrow.
	// setenv("SCRIPT_NAME", "/Users/sfearow/.brew/bin/php-cgi", 1); //  I'll think about that tomorrow.
	// setenv("SERVER_NAME", "webserv", 1);
	// setenv("SERVER_PORT", "8001", 1); //  I'll think about that tomorrow.
	// setenv("REDIRECT_STATUS", "CGI", 1); //  I'll think about that tomorrow.
	// setenv("SERVER_PROTOCOL", request.getProtocol().c_str(), 1);
	// setenv("SERVER_SOFTWARE", "WebServ/1.0", 1);
	// setenv("AUTH_TYPE", "", 1);
	// setenv("PATH_TRANSLATED", _response_path.c_str(), 1); //  I'll think about that tomorrow.
	// setenv("REMOTE_IDENT", "", 1);
	// setenv("REMOTE_USER", "", 1);
	// setenv("REDIRECT_STATUS", "200", 1);

	//  I'll think about that tomorrow.
// 	for (std::map<std::string, std::string>::iterator it = _requst_header.begin(), \
// 		it_end = _requst_header.end(); it != it_end; it++)
// 	{
// 		std::string tmp = it->first;
// 		for (int i = 0; i < tmp.size(); i++)
// 			tmp[i] = toupper(tmp[i]);
// 		setenv(("HTTP_" + tmp).c_str(), it->second.c_str(), 1);
// 	}
}

std::string Cgi::executeCgi(const std::string scriptName, Request &request, AConfig &config)
{
	std::string	newBody;
	status = "Status: 500\n";

	std::cout << "scriptName=" << scriptName << std::endl;

	// SAVING STDIN AND STDOUT IN ORDER TO TURN THEM BACK TO NORMAL LATER
	int saveStdin = dup(STDIN_FILENO);
	int saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);

	write(fdIn, request.getBody().c_str(), request.getBody().size());
	lseek(fdIn, 0, SEEK_SET);

	pid_t pid = fork();
	if (pid == -1)
	{
		throw std::runtime_error("Fork error");
	}
	else if (!pid)
	{
		extern char **environ;
		setEnv(request, config); //Cgi::_setEnv(Request &request, ConfigServer &config)
		// int iii = 0;
		// while (environ[iii]) {
		// 	std::cout << environ[iii] << std::endl;
		// 	iii++;
		// }
		char const	*cgi_cmd[3];
		cgi_cmd[0] = config.getCGIPath().c_str();
		cgi_cmd[1] = scriptName.c_str();
		cgi_cmd[2] = NULL;

		int i = 0;
		while (cgi_cmd[i])
		{
			std::cout << cgi_cmd[i] << std::endl;
			i++;
		}
		
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		if (execve(cgi_cmd[0], (char *const *)cgi_cmd, environ) == -1)
		{
			std::cerr << RED << "Execve error." << RESET << std::endl;
			// write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
			write(STDOUT_FILENO, "<center><p  style=\"font-size: 48px; font-weight:bold\">500</p>\
					<p  style=\"font-size: 48px; font-weight:bold\">Internal Server Error</p>\
					<p>An internal server error has occured</p>\n</center>", 179);
			exit(1);
		}
	}
	else
	{
		char	buffer[CGI_BUFSIZE] = {0};
		if (waitpid(pid, NULL, 0) == -1)
			throw "WAITPID ERROR";
		lseek(fdOut, 0, SEEK_SET);
		int ret;
		while ((ret = read(fdOut, buffer, CGI_BUFSIZE - 1)) != 0)
		{
			if (ret == -1)
				throw "READ CGI ERROR";
			newBody.append(buffer, ret);
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

	status = " 200 OK\n";
	return (newBody);
}
