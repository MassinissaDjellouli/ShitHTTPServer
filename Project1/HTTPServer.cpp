#include "HTTPServer.h"

ShitHTTP::HTTPServer* ShitHTTP::HTTPServer::create(int osFlag,int port = 8080) {
	HTTPServer* server = new ShitHTTP::HTTPServer(osFlag, port);
	ISocket* socket = server->socket;
	socket->startListening();
	return server;
}

void ShitHTTP::HTTPServer::startHandlingRequests() {
	this->socket->handleRequests(this->handler);
}
ShitHTTP::HTTPServer::HTTPServer(int osFlag,int port) {
	std::unordered_map<std::string, std::string> config;
	try {
		config = readConfigFile();
	}
	catch(int e){
		if (e == 1) {
			std::cout << "shithttp.conf not found or unable to be opened. Exiting with code 0.\n";
			exit(0);
		}
	}
	this->handlers = getDefaultHandlers();
	if (config.find("port") != config.end()) {
		port = stoi(config["port"]);
	}
	if (config.find("handler") != config.end()) {
		if (this->handlers.find(config["handler"]) != this->handlers.end()) {
			this->handler = this->handlers[config["handler"]];
		}
		else {
			std::cout << "Handler " << config["handler"] << " is not supported. Exiting with code 0\n";
			exit(0);
		}
	}
	else {
		this->handler = this->handlers["webserver"];
	}
	if (config.find("dir") != config.end()) {
		this->dir = config["dir"];
	}
	else {
		this->dir = "./dist";
	}
	this->osFlag = osFlag;
	setFactory();
	std::cout << "CreatedServer\n";

	ISocket* socket = factory->openSocket(port);
	if (socket == nullptr) {
		std::cout << "Factory failed to open socket at port " << port << ". Exiting with code 0.\n";
		exit(0);
	}
	this->socket = socket;
}
void ShitHTTP::HTTPServer::setFactory() {
	switch (osFlag) {
	case 0:
		std::cout << "Launching on Linux\n";
		exit(0);
	case 1:
		std::cout << "Launching on Windows\n";
		factory = dynamic_cast<IFactory*>(new ShitHTTP::WinFactory());
		break;
	default:
		exit(0);
	}
};
std::unordered_map<std::string, ShitHTTP::IHandler*> ShitHTTP::HTTPServer::getDefaultHandlers() {
	std::unordered_map<std::string, IHandler*> defaultHandlers;
	defaultHandlers["webserver"] = dynamic_cast<IHandler*>(new WebServerHandler());
	return defaultHandlers;
}
std::unordered_map<std::string, std::string> ShitHTTP::HTTPServer::readConfigFile() {
	std::ifstream file("shithttp.conf");
	std::string path = "./";
	if (!file.good()) {
		throw 1;
	}
	std::string line;
	std::unordered_map<std::string, std::string> config;
	while (getline(file, line)) {
		std::string key, value;
		key = line.substr(0, line.find('='));
		value = line.substr(line.find('=') + 1,std::string::npos);
		config[key] = value;
	}
	return config;
}
void ShitHTTP::HTTPServer::close() {
	this->socket->stop();
}

