#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "utils2.hpp"

class Response {
private:
	std::string _protocol;
	std::string _status;
	std::string _contentType;
	std::string _buffer;
	std::string _headers;
	std::string _body;
	std::map<std::string, std::string> _mine_types;

public:
	Response() : _contentType("Content-Type: "), _mine_types(init_mime_types()){}

	~Response(){}

	void setProtocol(const std::string& protocol) { _protocol = protocol; }
	void setStatus(const std::string& status) { _status = status; }
	void setContentType(const std::string& uri) {
		std::size_t found = uri.find_last_of('.');
		if (found == std::string::npos)
		{
			_contentType.append(_mine_types["txt"]);
		}
		else
		{
			std::string extension = uri.substr(found + 1);
			if (_mine_types.find(extension) != _mine_types.end())
				_contentType.append(_mine_types[extension]);
			else
				_contentType.append(_mine_types["bin"]);
		}
		_contentType.append("\n");
	}
	void setBuffer(const std::string& buffer) { _buffer = buffer; }
	void setHeader(const std::string& header) { _headers.append(header);}

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