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

const std::string& Request::getFileType() const { return file_type; }

void Request::setMethod(const std::string& a_method) { method = a_method; }

void Request::setUri(const std::string& a_uri) { 
	size_t pos = a_uri.find('?');
	if (pos == std::string::npos) {
		uri = a_uri;
	}
	else {
		uri = a_uri.substr(0, pos);
		size_t param_start = pos+1;
		get_param = a_uri.substr(param_start);
	}

	size_t dot_pos = uri.find_last_of('.');
	if (dot_pos != std::string::npos) {
		file_type = uri.substr(dot_pos+1);
	}
}

void Request::setProtocol(const std::string& a_protocol) { 
	if (!strncmp(a_protocol.c_str(), "HTTP/", 5))
		protocol = a_protocol; 
}

void Request::setHeader(const std::string& key, const std::string& value) { 
	headers.insert(std::make_pair(key, value)); 
}

void Request::setBody(const std::string &a_str) { body = a_str; }

bool Request::emptyHeader() const { return headers.empty(); }