#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include "ResponseBuilder.h"
namespace ShitHTTP {

class IHandler
{
public:
	virtual std::string handle(std::string input) = 0;
	IHandler(std::string dir);
	int getMethodFlag(std::string method);
protected:
	std::string unhandled();
	std::string dir;
};
}

