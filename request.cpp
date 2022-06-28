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

void Request::setUri(const std::string& a_uri) { 
	size_t pos = a_uri.find('?');
	if (pos == std::string::npos) {
		uri = a_uri;
		return;
	}
	uri = a_uri.substr(0, pos);
	size_t param_start = pos+1;
	size_t param_end = a_uri.find('#', param_start);
	std::string param;
	if (param_end != std::string::npos) {
		param = a_uri.substr(param_start, param_end-param_start);
		anchor = a_uri.substr(param_end+1);
	}
	else 
		param = a_uri.substr(param_start);
	
	size_t key_pos = pos + 1;
	do {
		size_t val_pos = a_uri.find('=', key_pos) + 1;
		std::string key = a_uri.substr(key_pos, val_pos - key_pos - 1);
		size_t end = a_uri.find('&', val_pos);
		std::string val;
		if (end != std::string::npos) {
			val = a_uri.substr(val_pos, end - val_pos);
			key_pos = end+1;
		}
		else {
			val = a_uri.substr(val_pos);
			key_pos = end;
		}
		get_param.insert(std::make_pair(key, val));
	} while (key_pos != std::string::npos);

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