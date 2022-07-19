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
	std::string _return;
	std::map<std::string, std::string> _mine_types;

public:
	Response() : _contentType("Content-Type: "), _mine_types(init_mime_types()){}

	Response(const Response& other) {
		if (this != &other)
		{
			_protocol = other._protocol;
			_status = other._status;
			_contentType = other._contentType;
			_buffer = other._buffer;
			_headers = other._headers;
			_body = other._body;
			_return = other._return;
			_mine_types = other._mine_types;
		}
	}
	~Response(){}

	void setProtocol(const std::string& protocol) { _protocol = protocol; }
	void setStatus(const std::string& status) { _status = status; }
	void setContentType(Request& requst) {
		std::string type = requst.getHeader("Content-Type");
		if (!type.empty())
		{
			_contentType.append(type);
			_contentType.append("\n");
			return ;
		}
		std::map<std::string, std::string>::iterator it;
		if ((it = _mine_types.find(requst.getFileType())) != _mine_types.end())
			_contentType.append(it->second);
		else
			_contentType.append(_mine_types["bin"]);
		_contentType.append("\n");
	}
	void setBuffer(const std::string& buffer) { _buffer = buffer; }
	// void setHeader(const std::string& header) { _headers.append(header);}
	void setReturn(std::string& status, std::string redirect)
	{
		_status = status;
		_return = "Location:" + redirect + "\r\n";
	}

	void setBody(const std::string& body) { _body = body; }
	const std::string& getProtocol() const { return _protocol; }
	const std::string& getStatus() const { return _status; }
	const std::string& getBuffer() const { return _buffer; }
	const std::string& getContentType() const { return _contentType; }
	const std::string& getHeaders() const { return _headers; }
	const std::string& getBody() const { return _body; }

	std::string handlerBody(std::string& body) {
		size_t end;
		std::string status = "200";
		while ((end = body.find("\r\n")) != std::string::npos)
		{
			std::vector<std::string> cgi_body_split= ft_split(_body.substr(0, end), " ");	
			if (!cgi_body_split.empty() && cgi_body_split[0] == "Status:")
			{
				if (cgi_body_split[1] != "200")
					return status = "500";
			}
			else if (!cgi_body_split.empty() && cgi_body_split[0] == "Content-Type:")
				_contentType = body.substr(0, end);
			body.erase(0, end + 2);
		}
		return status;
	}
    

	void createHeader() { 
		_headers = _protocol + _status + _contentType + "Content-Length: " + std::to_string(_body.size()) + "\n\n";
		if (!_return.empty())
			_headers += _return;
	}

};

#endif