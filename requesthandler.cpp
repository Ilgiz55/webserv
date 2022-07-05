#include "requesthandler.hpp"

RequestHandler::RequestHandler(FdHandler *s, Request& req, Response& res) : isfile(true), static_site(true), request(req), response(res) {
	conf = s->GetConfigServer();
}

void RequestHandler::Handle() {
	ParseFileType();
	GetPath();
	std::string method = request.getMethod();
	if (method == "GET")
		this->Get();
	else if (method == "POST")
		this->Post();
	else if (method == "DELETE")
		this->Delete();
}

void RequestHandler::ParseFileType() {

	std::string uri = request.getUri();
	uri = "/images/";
	uri = "/panda.html";

	// std::string file_type;
	size_t pos = uri.find_last_of('.');
	if (pos == std::string::npos) {
		isfile = false;
		return;
	}
	size_t pos_end = uri.find('/', pos+1);
	if (pos_end == std::string::npos) 
		file_type = uri.substr(pos+1);
	else 
		file_type = uri.substr(pos+1, pos_end - pos);

	if (file_type == "php")
		static_site = false;
	
}

void RequestHandler::GetPath() {
	std::map<std::string, Location> loc;
	loc = conf.getLocation();
	std::string uri = request.getUri();
	std::map<std::string, Location>::iterator it;
	for (it = loc.begin(); it != loc.end(); ++it) {
		size_t pos = it->first.find(file_type.c_str());
		if (pos != std::string::npos) {
			path = it->second.getRoot() + request.getUri();
			return;
		}
	}

	for  (it = loc.begin(); it != loc.end(); ++it) {
		size_t pos = uri.find(it->first);
		if(pos != std::string::npos) {
			path = it->second.getRoot() + request.getUri();
			return;
		}
	}

	path = conf.getRoot();
}

void RequestHandler::Get() {
	if (static_site && isfile) {
		try {
			response.setBody(read_file(path));
			response.setStatus(" 200 OK\n");
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << std::endl;
			response.setBody("FILE NOT FOUND\n");
			response.setStatus(" 404 Not Found\n");
		}
	}
	else if (!isfile) {
		// list of files and folders
		response.setBody("here will be the list of files and folders, but I don't know hot to do it for now");
		response.setStatus(" 200 OK\n");
	}
	else if (!static_site && isfile) {
		// cgi
		response.setBody("here will be the result of cgi work");
		response.setStatus(" 200 OK\n");
	}
}

void RequestHandler::Post() {

}

void RequestHandler::Delete() {

}