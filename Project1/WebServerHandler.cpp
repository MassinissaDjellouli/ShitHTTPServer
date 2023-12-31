#include "WebServerHandler.h"

std::string ShitHTTP::WebServerHandler::handle(std::string input) {
	std::cout << input;
	std::string msg = "Hello world!";
	RequestBuilder* builder = new RequestBuilder();
	std::string response = builder->
		createRequest()->
		addHeader("Content-Type", "text/html; charset=utf-8")->
		addHeader("Server", "ShitHTTP")->
		addHeader("Content-Length", std::to_string(msg.size()))->
		addBody(msg)->
		build();
	return response;
}

std::string ShitHTTP::WebServerHandler::getFileContent(std::string path) {

}