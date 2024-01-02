#include "HTTPServer.h"

ShitHTTP::HTTPServer* ShitHTTP::HTTPServer::create(int port = 8080) {
	int osFlag;
	#if __linux__
		osFlag = 0;
	#elif _WIN32
		osFlag = 1;
	#else
		osFlag = 2;
	#endif
	HTTPServer* server = new ShitHTTP::HTTPServer(osFlag, port);
	ISocket* socket = server->socket;
	socket->startListening();
	return server;
}

void ShitHTTP::HTTPServer::startHandlingRequests() {
	if (this->config.find("handler") != this->config.end()) {
		if (this->handlers.find(this->config["handler"]) != this->handlers.end()) {
			std::cout << "Using handler " << this->config["handler"] << "\n";
			this->handler = this->handlers[this->config["handler"]];
		}
		else {
			std::cout << "Handler " << this->config["handler"] << " is not supported. Exiting with code 0\n";
			exit(0);
		}
	}
	else {
		std::cout << "Using default handler\n";
		this->handler = this->handlers["webserver"];
	}
	this->socket->handleRequests(this->handler);
}
ShitHTTP::HTTPServer::HTTPServer(int osFlag,int port) {
	try {
		this->config = readConfigFile();
	}
	catch(int e){
		if (e == 1) {
			std::cout << "shithttp.conf not found or unable to be opened. Exiting with code 0.\n";
			exit(0);
		}
	}
	if (this->config.find("port") != this->config.end()) {
		port = stoi(this->config["port"]);
	}
	if (this->config.find("dir") != this->config.end()) {
		this->dir = this->config["dir"];
	}
	else {
		this->dir = "./dist";
	}
	this->handlers = getDefaultHandlers();

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
	std::cout << "D: " + this->dir << "\n";
	defaultHandlers["webserver"] = dynamic_cast<IHandler*>(new BasicWebServerHandler(this->dir));
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
	file.close();
	return config;
}
void ShitHTTP::HTTPServer::close() {
	this->socket->stop();
}

void ShitHTTP::HTTPServer::addHandler(std::string name,IHandler* handler) {
	this->handlers[name] = handler;
}