#include "BasicRestHandler.h"
void ShitHTTP::BasicRestHandler::addRoute(std::string route, std::string method, std::function<std::string(std::string)> func) {
	routes[method + "::" + route] = func;
}

std::string ShitHTTP::BasicRestHandler::handle(std::string input) {
	std::cout << input << "\n";
	std::list<std::string> lines = StringUtils::split(input, "\n");

	std::string firstLine = lines.front();
	std::list<std::string> firstLineTokens = StringUtils::split(firstLine, " ");
	std::string method = firstLineTokens.front();

	firstLineTokens.pop_front();
	std::string path = firstLineTokens.front();
	lines.pop_front();
	if (routes.find(method + "::" + path) == routes.end()) {
		return unhandled();
	}
	return routes[method + "::" + path](input);
}

ShitHTTP::BasicRestHandler::BasicRestHandler() : IHandler("") {}