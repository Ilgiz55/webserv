#include "session.hpp"

#include <stdio.h>

Session::Session(Server *a_master, int fd) : FdHandler(fd, true), master(a_master) {}

Session::~Session() {}

void Session::Send(const char *msg) {
	write(GetFd(), msg, strlen(msg));
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


void Session::Handle(bool r, bool w) {
	if (!r)
		return;
	char answer[] = "\
	HTTP/1.1 200 OK\r\n\
	Version: HTTP/1.1\r\n\
	Content-Type: text/html; charset=utf-8\r\n\
	Content-Length: 88\r\n\r\n\
	<html>hello from my server\n</html>";

	Receive();
	Parse();
	std::cout << req << std::endl;
	Send(answer);
	master->RemoveSession(this);

}