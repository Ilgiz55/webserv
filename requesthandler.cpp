#include "requesthandler.hpp"

RequestHandler::RequestHandler(ConfigServer conf, Request& req, Response& res) : conf_serv(conf),  isfile(true), static_site(true), request(req), response(res) {}

void RequestHandler::Handle() {
	AConfig conf = GetConf();
	std::string method = request.getMethod();
	if (method == "GET")
		this->Get(conf);
	else if (method == "POST")
		this->Post();
	else if (method == "DELETE")
		this->Delete();
}

AConfig RequestHandler::GetConf() {
	std::map<std::string, Location> loc;
	loc = conf_serv.getLocation();
	std::string uri = request.getUri();
	if (loc.empty()) {
		path = conf_serv.getRoot() + uri;
		return conf_serv;
	}
	std::map<std::string, Location>::iterator it;
	size_t len = 0;
	for (it = loc.begin(); it != loc.end(); ++it) {
		if (uri.find(it->first) != std::string::npos) {
			if (it->first.length() > len) {
				path = it->second.getRoot() + uri;
				location = it->second;
				len = it->first.length();
			}
		}
	}
	if (!request.getFileType().empty()){
		for (it = loc.begin(); it != loc.end(); ++it) {
			if (it->first.find(request.getFileType()) != std::string::npos) {
				path = it->second.getRoot() + uri;
				location = it->second;
				break;
			}
		}
	}
	return location;
}

void RequestHandler::GetForFile(std::string path, AConfig conf) {
	if (conf.getCGIPath().empty()) { 
		if (isThereSuchFile(path)) {
			response.setBody(read_file(path));
			response.setStatus(" 200 OK\n");
		}
		else {
			response.setBody("FILE NOT FOUND\n");
			response.setStatus(" 404 Not Found\n");
		}
	}
	else {
			//CGI work
	}
}

void RequestHandler::Get(AConfig& conf) {
	if (!request.getFileType().empty())  // if file
		GetForFile(path, conf);
	else {
		if (isThereSuchDir(path)) {
			if (conf.getAutoIndex()) {
				//autoindex work
			}
			else if (!conf.getIndex().empty()) {
				request.setUri(request.getUri() + conf.getIndex());
				AConfig new_conf = GetConf();
				Get(new_conf);
			}
			else {
				// some error then we don't have index rule
				response.setBody("some error then we don't have index rule\n");
				response.setStatus(" 404 Not Found\n");
			}
		}
		else {
			response.setBody("DIRECTORY NOT FOUND\n");
			response.setStatus(" 404 Not Found\n");
		}
	}
}



void RequestHandler::Post() {

}

void RequestHandler::Delete() {

}