#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>

class Response {
private:
	std::string _protocol;
	std::string _status;
	std::string _contentType;
	std::string _buffer;
	std::string _headers;
	std::string _body;

public:
	Response(){}

	~Response(){}

	void setProtocol(const std::string& protocol) { _protocol = protocol; }
	void setStatus(const std::string& status) { _status = status; }
	void setContentType(const std::string& contentType) { _contentType = contentType; }
	void setBuffer(const std::string& buffer) { _buffer = buffer; }
	void setHeader() { 
		_headers = _protocol + _status + _contentType;
		_headers = _headers + "Server: webserv\n\n";
	}
	void setBody(const std::string& body) { _body = body; }
	const std::string& getProtocol() const { return _protocol; }
	const std::string& getStatus() const { return _status; }
	const std::string& getBuffer() const { return _buffer; }
	const std::string& getContentType() const { return _contentType; }
	const std::string& getHeaders() const { return _headers; }
	const std::string& getBody() const { return _body; }

private:
	Response(const Response&);
	Response& operator=(const Response&);
    
};

#endif