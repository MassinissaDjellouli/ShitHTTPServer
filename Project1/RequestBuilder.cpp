#include "RequestBuilder.h"
ShitHTTP::RequestBuilder* ShitHTTP::RequestBuilder::addHeader(std::string key, std::string value) {
	this->request["header"].push_back(key + " : " + value);
	return this;
}
ShitHTTP::RequestBuilder* ShitHTTP::RequestBuilder::addBody(std::string body) {
	std::list<std::string> lbody = this->request["body"];
	if (lbody.size() == 1) {
		lbody.empty();
	}
	lbody.push_back(body);
	return this;
}
ShitHTTP::RequestBuilder* ShitHTTP::RequestBuilder::createRequest() {
	std::list<std::string> headerList;
	std::list<std::string> bodyList;
	request["header"] = headerList;
	request["body"] = bodyList;
	return this;
}

std::string ShitHTTP::RequestBuilder::build() {
	std::string response;
	std::string head = "HTTP/1.1 " + std::to_string(this->status) + " " + HttpStatus::reasonPhrase(this->status) + "\n";
	response.append(head);
	for (std::string line : request["header"])
		response.append(line + "\n");
	response.append("\n" + request["body"].back());
	return response;
}