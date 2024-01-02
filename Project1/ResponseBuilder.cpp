#include "ResponseBuilder.h"
ShitHTTP::ResponseBuilder* ShitHTTP::ResponseBuilder::addHeader(std::string key, std::string value) {
	this->response["header"].push_back(key + " : " + value);
	return this;
}
ShitHTTP::ResponseBuilder* ShitHTTP::ResponseBuilder::addBody(std::string body) {
	std::list<std::string> lbody = this->response["body"];
	if (lbody.size() == 1) {
		lbody.empty();
	}
	lbody.push_back(body);
	response["body"] = lbody;
	return this;
}
ShitHTTP::ResponseBuilder* ShitHTTP::ResponseBuilder::createResponse() {
	std::list<std::string> headerList;
	std::list<std::string> bodyList;
	response["header"] = headerList;
	response["body"] = bodyList;
	return this;
}

ShitHTTP::ResponseBuilder* ShitHTTP::ResponseBuilder::statusCode(int status) {
	this->status = (HttpStatus::Code)status;
	return this;
}
std::string ShitHTTP::ResponseBuilder::build() {
	std::string responseString;
	std::string head = "HTTP/1.1 " + std::to_string(this->status) + " " + HttpStatus::reasonPhrase(this->status) + "\n";
	responseString.append(head);
	for (std::string line : response["header"])
		responseString.append(line + "\n");
	responseString.append("\n" + response["body"].back());
	return responseString;
}