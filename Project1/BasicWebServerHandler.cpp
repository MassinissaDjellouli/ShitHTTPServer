#include "BasicWebServerHandler.h"

std::string ShitHTTP::BasicWebServerHandler::handle(std::string input) {
	std::cout << input << "\n";
	std::list<std::string> lines = StringUtils::split(input, "\n");

	std::string firstLine = lines.front();
	std::list<std::string> firstLineTokens = StringUtils::split(firstLine, " ");
	std::string method = firstLineTokens.front();
	int methodFlag = 0;
	if(method == "GET") {
		methodFlag = 0;
	}
	else if (method == "POST") {
		methodFlag = 1;
	}
	else if (method == "PUT") {
		methodFlag = 2;
	}
	else if (method == "DELETE") {
		methodFlag = 3;
	}
	else if (method == "HEAD") {
		methodFlag = 4;
	}
	else if (method == "OPTIONS") {
		methodFlag = 5;
	}
	else if (method == "TRACE") {
		methodFlag = 6;
	}
	else if (method == "CONNECT") {
		methodFlag = 7;
	}
	else {
		methodFlag = -1;
	}	
	firstLineTokens.pop_front();
	lines.pop_front();
	switch (methodFlag) {
		case 0:
			return handleGet(lines,firstLineTokens.front());
			break;
		default:
			return unhandled();
			break;
	}
}

std::string ShitHTTP::BasicWebServerHandler::getFileContent(std::string path) {
	if (path == "/") {
		path = "/index.html";
	}
	std::cout << "path : " + dir + path << "\n";
	std::ifstream file(dir + path);
	if (!file.good()) {
		return "";
	}
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return content;
}

ShitHTTP::BasicWebServerHandler::BasicWebServerHandler(std::string dir):IHandler(dir){}
std::string ShitHTTP::BasicWebServerHandler::handleGet(std::list<std::string> input, std::string path) {
	int statusCode = 200;
	std::string msg = getFileContent(path);
	if (msg.size() == 0) {
		msg = "404 Not Found";
		statusCode = 404;
	}
	ResponseBuilder* builder = new ResponseBuilder();
	std::string response = builder->
		createResponse()->
		statusCode(statusCode)->
		addHeader("Content-Type", "text/html; charset=utf-8")->
		addHeader("Server", "ShitHTTP")->
		addHeader("Content-Length", std::to_string(msg.size()))->
		addBody(msg)->
		build();
		std::cout << response << "\n";
		std::cout << "Sent Response with code " + std::to_string(statusCode) +"\n";
		return response;
}

std::string ShitHTTP::BasicWebServerHandler::unhandled() {
	std::string msg = "Method not implemented";
	ResponseBuilder* builder = new ResponseBuilder();
	std::string response = builder->
		createResponse()->
		statusCode(405)->
		addHeader("Content-Type", "text/html; charset=utf-8")->
		addHeader("Server", "ShitHTTP")->
		addHeader("Content-Length", std::to_string(msg.size()))->
		addBody(msg)->
		build();
	std::cout << response << "\n";
	return response;
}