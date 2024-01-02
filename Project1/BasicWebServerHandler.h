#pragma once
#include "IHandler.h"
#include "ResponseBuilder.h"
#include <iostream>
#include <string>
#include "StringUtils.h"
#include <fstream>
namespace ShitHTTP {

class BasicWebServerHandler: public IHandler
{
public:
	std::string handle(std::string input);
	std::string getFileContent(std::string path);
	BasicWebServerHandler(std::string dir);
protected:
	std::string handleGet(std::list<std::string> input,std::string path);
};
}

