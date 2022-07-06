#include "session.hpp"

#include <stdio.h>

Session::Session(ConfigServer _config, Server *a_master, int fd) : FdHandler(_config, fd, true), master(a_master)/*, config(_config)*/ {}

Session::~Session() {}

void Session::Send() {
	std::string buffer = response.getBuffer();
	ssize_t sendBytes = send(GetFd(), buffer.c_str(), buffer.size(),0);
}

void Session::Receive() {
	
	int rc;
	while ((rc = recv(GetFd(), buffer, sizeof(buffer), 0)) > 0) {
		if (rc >= (int)sizeof(buffer)){
			req.append(buffer);
		}
		else {
			break;
		}
	}
	req.append(buffer, 0, rc);
	
}

void Session::Parse() {
	size_t pos = req.find("\r\n\r\n");
	request.setBody(req.substr(pos + 4));
	req = req.substr(0, pos+2);
	std::vector<std::string> h = ft_split(req, "\r\n");
	std::string firstline = h[0];
	size_t start;
	size_t end = firstline.find(' ');
	if (end == std::string::npos)
		return;
	request.setMethod(firstline.substr(0, end));
	start = end + 1;
	end = firstline.find(' ', start);
	if (end == std::string::npos)
		return;
	request.setUri(firstline.substr(start, end - start));
	start = end + 1;
	if (start > firstline.length())
		return;
	request.setProtocol(firstline.substr(start));


	for(size_t i = 1; i < h.size(); ++i) {
		pos = h[i].find(": ");
		if (pos == std::string::npos)
			continue;
		std::string key = h[i].substr(0, pos);
		std::string value = h[i].substr(pos + 2);
		request.setHeader(key, value);
	}
}

void Session::SetResponse(){
	if (request.getMethod() == "GET")
	{
		std::cout << "_____________________________________\n";
		response.setProtocol(request.getProtocol());
		std::cout << "URI: " << request.getUri() << std::endl;
		std::cout << "Body: " << request.getBody() << std::endl;
		// std::cout << "Body: " << request.getBody() << std::endl;
		std::string file_name = this->GetConfigServer().getRoot() + request.getUri();
		if (request.getUri().find_last_of('.') == std::string::npos)
		{
			file_name += "/" + this->GetConfigServer().getIndex();
		}
		if (request.getUri().find_last_of(".php") != std::string::npos)
		{
			int fd[2];
			pid_t id;
			if (pipe(fd) == -1)
				exit_error(e.what(), 1);
			id = fork();
			if (id == -1)
			{
				std::error << "fork\n";
				exit_error(e.what(), 1);
			}
		}
		try
		{
			response.setBody(read_file(file_name));
		}
		catch(const std::exception& e)
		{
			std::cerr << "response   !!!" << std::endl;
			std::cerr << e.what() << std::endl;
			response.setBody("NOT FOUND\n");
		}
		response.setStatus(" 200 OK\n");
		response.setContentType(request.getUri());
		response.setHeader(response.getProtocol() + response.getStatus() + response.getContentType());
		response.setHeader("Content-Length: " + std::to_string(response.getBody().size()) + "\n\n");
		response.setBuffer(response.getHeaders() + response.getBody());
		std::cout << "________________________________\n";
	}
	else if (request.getMethod() == "POST")
	{}
	else if (request.getMethod() == "DELETE")
	{}
}

// void Session::SetResponse(){
// 	response.setProtocol(request.getProtocol());
// 	response.setStatus(" 200 OK\n");
// 	response.setContentType(request.getUri());
// 	try
// 	{
// 		std::string file_name = this->GetConfigServer().getRoot() + request.getUri();
// 		response.setBody(read_file(file_name));
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << std::endl;
// 		response.setBody("NOT FOUND\n");
// 	}
// 	response.setHeader(response.getProtocol() + response.getStatus() + response.getContentType());
// 	response.setHeader("Content-Length: " + std::to_string(response.getBody().size()) + "\n\n");
// 	response.setBuffer(response.getHeaders() + response.getBody());
// }

void Session::Handle(bool r, bool w) {
	if (!r)
		return;
	Receive();
	try
	{
		/* code */
		Parse();
		std::cout << req << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "!!!!!!!!! Handle BLOCK !!!!!!!!!! ERROR" << std::endl;
		std::cerr << e.what() << '\n';
		exit_error(e.what(), 1);
	}
	SetResponse();
	Send();
	
	master->RemoveSession(this);

}
