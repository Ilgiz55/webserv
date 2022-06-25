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
	Response();

	~Response();

	void setProtocol(const std::string& protocol);

	void setStatus(const std::string& status);

	void setContentType(const std::string& contentType);

	void setBuffer(const std::string& buffer);

	void setHeader(const std::string& header);

	void setBody(const std::string& body);

	const std::string& getProtocol() const;

	const std::string& getStatus() const;

	const std::string& getBuffer() const;

	const std::string& getContentType() const;

	const std::string& getHeaders() const;

	const std::string& getBody() const;

private:
	Response(const Response&);

	Response& operator=(const Response&);
};

#endif