#include "CustomRestHandlerExample.h"
ShitHTTP::CustomRestHandlerExample::CustomRestHandlerExample() {
	addRoute("/test", "GET", [&](std::string input) {
		ResponseBuilder* builder = new ResponseBuilder();
		std::string response = builder->
			createResponse()->
			statusCode(200)->
			addHeader("Content-Type", "text/html; charset=utf-8")->
			addHeader("Server", "ShitHTTP")->
			addHeader("Content-Length", std::to_string(4))->
			addBody("test")->
			build();
		std::cout << response << "\n";
		return response;
		});

	addRoute("/test", "POST", [&](std::string input) {
		ResponseBuilder* builder = new ResponseBuilder();
		std::string response = builder->
			createResponse()->
			statusCode(201)->
			addHeader("Content-Type", "text/html; charset=utf-8")->
			addHeader("Server", "ShitHTTP")->
			addHeader("Content-Length", std::to_string(4))->
			addBody("test")->
			build();
		std::cout << response << "\n";
		return response;
		});

	addRoute("/test2", "GET", [&](std::string input) {
		ResponseBuilder* builder = new ResponseBuilder();
		std::string response = builder->
			createResponse()->
			statusCode(200)->
			addHeader("Content-Type", "text/html; charset=utf-8")->
			addHeader("Server", "ShitHTTP")->
			addHeader("Content-Length", std::to_string(5))->
			addBody("test2")->
			build();
		std::cout << response << "\n";
		return response;
		});
}