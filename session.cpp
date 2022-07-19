#include "session.hpp"

#include <stdio.h>

Session::Session(ConfigServer _config, Server *a_master, int fd) : FdHandler(_config, fd, true), master(a_master)/*, config(_config)*/ {}

Session::~Session() {}

Request& Session::GetRequest() {return request; }
Response& Session::GetResponse() {return response; }

void Session::Send() {
	std::string buffer = response.getBuffer();
	ssize_t sendBytes = send(GetFd(), buffer.c_str(), buffer.size(),0);
	if (sendBytes < 0)
		throw std::runtime_error("Error send response");
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
	if (h.empty())
		return;
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
	response.setProtocol(request.getProtocol());
	response.setStatus(response.getStatus());
	response.setContentType(request);
	// try
	// {
	// 	std::string file_name = this->GetConfigServer().getRoot() + request.getUri();
	// 	response.setBody(read_file(file_name));
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << std::endl;
	// 	response.setBody("NOT FOUND\n");
	// }
	response.setHeader(response.getProtocol() + response.getStatus() + response.getContentType());
	response.setHeader("Content-Length: " + std::to_string(response.getBody().size()) + "\n\n");
	response.setBuffer(response.getHeaders() + response.getBody());
}

void Session::Handle(bool r, bool w) {
	// (void)w;
	if (!r)
		return;
	Receive();
	try {
		Parse();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "error in parse" << std::endl;
	}
	std::cout << req << std::endl;
	RequestHandler rh(this->GetConfigServer(), request, response);
	rh.Handle();
	SetResponse();
	// std::string buffer = response.getBuffer();
	try {
		Send();
	}   
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "error in send" << std::endl;
	}
	master->RemoveSession(this);

}
