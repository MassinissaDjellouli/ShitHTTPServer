#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
namespace ShitHTTP {

class IHandler
{
public:
	virtual std::string handle(std::string input) = 0;
	IHandler(std::string dir);
protected:
	std::string dir;
};
}

