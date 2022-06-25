#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>

#include <map>
#include <string.h>

class Request {
	private:
		std::string method;
		std::string uri;
		std::string protocol;
		std::map<std::string, std::string> headers;
		std::string body;

	public:
		Request();
		~Request();
		const std::string& getMethod() const;
		const std::string& getUri() const;
		const std::string& getProtocol() const;
		std::string getHeader(const std::string& key) const;
		const std::string& getBody() const;
		
		void setMethod(const std::string& a_method);
		void setUri(const std::string& a_uri);
		void setProtocol(const std::string& a_protocol);
		void setHeader(const std::string& key, const std::string& value);
		void setBody(const std::string &a_str);
		bool emptyHeader() const;

};


#endif