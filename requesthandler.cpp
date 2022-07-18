#include "requesthandler.hpp"
#include "./cgi/CGI.hpp"

RequestHandler::RequestHandler(ConfigServer config, Request& req, Response& res) : conf_serv(config),  isfile(true), static_site(true), request(req), response(res) {}

void RequestHandler::Handle() {
	AConfig conf = GetConf();
	std::string method = request.getMethod();
	std::vector<std::string>::iterator it = conf.getMethods().begin();
	if (!conf.getMethods().empty()) {
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
		this->Post(conf);
	else if (method == "DELETE")
		this->Delete(conf);
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
	// std::cout << "-----TEST GetForFile-----" <<std::endl;
	// std::cout << path <<std::endl;
	if (conf.getCGIPath().empty()) { 
		if (isThereSuchFile(path)) {
			response.setBody(read_file(path));
			response.setStatus(" 200 OK\n");
		}
		else {
			response.setBody("<p  style=\"font-size: 24px; font-weight:bold\"><b>Not Found</p></b><p>The requested URL was not found on this server.</p>\n");
			response.setStatus(" 404 Not Found\n");
		}
	}
	else {
		//CGI work
		Cgi cgi;
		try
		{
			std::string body = cgi.executeCgi(path, request,conf);
			
			response.setBody(body);
			response.setStatus(cgi.status);
		}
		catch(const std::exception& e)
		{
			response.setBody("<center><p  style=\"font-size: 48px; font-weight:bold\">500</p>\
					<p  style=\"font-size: 48px; font-weight:bold\">Internal Server Error</p>\
					<p>An internal server error has occured</p>\n</center>");
			response.setStatus(cgi.status);
			std::cerr << e.what() << std::endl;
		}
		std::cout << "-----PRINT BODY-----" <<std::endl;
		std::cout << response.getBody() << std::endl;
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

void RequestHandler::Post(AConfig& conf) {
	// std::cout << "-----handeling post method-----" << std::endl;
	// std::cout << "Body of post request:\n" << request.getBody() << std::endl << std::endl;
	Get(conf);

}

void RequestHandler::Delete(AConfig& conf) {
	// std::cout << "-----handeling delete method-----" << std::endl;
	// std::cout << "file to delete: " << path << std::endl;
	if (isThereSuchFile(path)) {
		if (remove(path.c_str()) != 0)
			perror("Can't delete file");
		else {
			response.setBody("<html>File deleted</html>");
			response.setStatus("200 OK");
		}
	}
	else {
		response.setBody("file not found");
		response.setStatus("404 Not found\n");
	}
}