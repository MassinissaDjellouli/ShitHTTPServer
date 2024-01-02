#include "IHandler.h"
ShitHTTP::IHandler::IHandler(std::string dir) {
	this->dir = dir;
}

int ShitHTTP::IHandler::getMethodFlag(std::string method) {
	if (method == "GET") {
		return 0;
	}
	if (method == "POST") {
		return 1;
	}
	if (method == "PUT") {
		return 2;
	}
	if (method == "DELETE") {
		return 3;
	}
	if (method == "HEAD") {
		return 4;
	}
	if (method == "CONNECT") {
		return 5;
	}
	if (method == "OPTIONS") {
		return 6;
	}
	if (method == "TRACE") {
		return 7;
	}
	return -1;
}
std::string ShitHTTP::IHandler::unhandled() {
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