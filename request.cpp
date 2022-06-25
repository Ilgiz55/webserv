#include "request.hpp"

Request::Request() {}

Request::~Request() {}

const std::string& Request::getMethod() const { return method; }

const std::string& Request::getUri() const { return uri; }

const std::string& Request::getProtocol() const { return protocol; }

std::string Request::getHeader(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it = headers.find(key);
	if (it == headers.end())
		return "";
	return it->second;
}

const std::string& Request::getBody() const { return body; }

void Request::setMethod(const std::string& a_method) { method = a_method; }

void Request::setUri(const std::string& a_uri) { uri = a_uri;}

void Request::setProtocol(const std::string& a_protocol) { 
	if (!strncmp(a_protocol.c_str(), "HTTP/", 5))
		protocol = a_protocol; 
}

void Request::setHeader(const std::string& key, const std::string& value) { 
	headers.insert(std::make_pair(key, value)); 
}

void Request::setBody(const std::string &a_str) { body = a_str; }

bool Request::emptyHeader() const { return headers.empty(); }