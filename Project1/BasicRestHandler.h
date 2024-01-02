#pragma once
#include "IHandler.h"
#include "StringUtils.h"
#include <iostream>
#include <unordered_map>
#include <functional>
namespace ShitHTTP {

class BasicRestHandler : public IHandler
{
public:
	std::string handle(std::string input);
protected:
	void addRoute(std::string route,std::string method,std::function<std::string(std::string)> func);
	std::unordered_map<std::string, std::function<std::string(std::string)>> routes;
	BasicRestHandler();
};
}

