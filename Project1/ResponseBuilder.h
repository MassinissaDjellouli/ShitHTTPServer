#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include "HTTPStatus.h"
namespace ShitHTTP {

class ResponseBuilder
{
public:
	ResponseBuilder* createResponse();
	ResponseBuilder* addHeader(std::string key, std::string value);
	ResponseBuilder* addBody(std::string body);
	ResponseBuilder* statusCode(int status);
	std::string build();
private:
	HttpStatus::Code status;
	std::unordered_map<std::string, std::list<std::string>> response;
};
	}

