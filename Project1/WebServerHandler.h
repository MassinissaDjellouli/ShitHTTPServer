#pragma once
#include "IHandler.h"
#include "RequestBuilder.h"
#include <iostream>
namespace ShitHTTP {

class WebServerHandler: public IHandler
{
	std::string handle(std::string input);
	std::string getFileContent(std::string path);
};
}

