#include "requesthandler.hpp"

RequestHandler::RequestHandler(ConfigServer conf, Request& req, Response& res) : conf_serv(conf),  isfile(true), static_site(true), request(req), response(res) {}

void RequestHandler::Handle() {
	AConfig conf = GetConf();
	std::string method = request.getMethod();
	if (!conf.getMethods().empty()) {
		std::vector<std::string>::iterator it = conf.getMethods().begin();
		for (; it != conf.getMethods().end(); ++it) {
			if (method == *it)
				break;
		}
		if (it == conf.getMethods().end()){
			response.setBody("method not allowed\n");
			response.setStatus(" "); // add status code
		}
	}
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
				path = it->second.getRoot() + uri.substr(uri.find_last_of("/"));
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

void RequestHandler::AutoIndex() {
	DIR *dir;
	struct dirent *entry;
	dir = opendir(path.c_str());
	if (!dir) {
		response.setStatus(" 403\n");
		return;
	}
	std::string body;
	body = "<!DOCTYPE html>\n\
			<html>\n\
			<head>\n\
			    <title> List of files </title>\n\
			    <style>h1 {font-size: 200%;\n\
			    font-family: Verdana, Arial, Helvetica, sans-serif;\n\
			    color: #333366;}\n\
			    a {font-size: 100%;\
			    font-family: Verdana, Arial, Helvetica, sans-serif;\n\
			    color: #333366;}\n\
			    li :hover{font-size: 100%;\
			    font-family: Verdana, Arial, Helvetica, sans-serif;\n\
			    color: #ba2200;}\n\
			    li :active{font-size: 100%;\
			    font-family: Verdana, Arial, Helvetica, sans-serif;\n\
			    color: #918e00;}\n\
			<style>footer {\n\
			    position: fixed;\n\
			    color: #333366;}\n\
			    left: 0; bottom: 0;\n\
			    color: #333366;}\n\
			</style>\n\
			</head>\n\
			<body>\n\
			<h1 align=\"center\"> List of files</h1>\n";
	while ((entry = readdir(dir)) != NULL) {
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;
		body.append("<li align=\"center\"> <a href = \"http://");
		body.append(request.getHeader("Host") + request.getUri());
		if (request.getFileType().empty() && (request.getUri().at(request.getUri().length() - 1) != '/'))
			body.append("/");
		body.append(entry->d_name);
		body.append("\">");
		body.append(entry->d_name);
		body.append("</a></li><br>");
		body.append("\n");
	}
	body.append("</body>\n </html>\n");
	std::cout << body << std::endl;
	response.setBody(body);
	response.setStatus(" 200 OK\n");
}

void RequestHandler::Get(AConfig& conf) {
	if (!request.getFileType().empty())
		GetForFile(path, conf);
	else if (isThereSuchDir(path) && conf.getAutoIndex())
		AutoIndex();
	else {
		std::string new_uri = request.getUri();
		if (new_uri.at(new_uri.length() - 1) != '/')
			new_uri.append("/");
		new_uri.append(conf.getIndex());
		request.setUri(new_uri);
		AConfig new_conf = GetConf();
		Get(new_conf);
	}
}



void RequestHandler::Post() {
	std::cout << request.getBody() << std::endl;
}

void RequestHandler::Delete() {

}