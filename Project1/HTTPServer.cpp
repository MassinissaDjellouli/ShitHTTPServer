#include "HTTPServer.h"

ShitHTTP::HTTPServer* ShitHTTP::HTTPServer::create(int osFlag,int port) {
	HTTPServer* server = new ShitHTTP::HTTPServer(osFlag, port);
	ISocket* socket = server->socket;
	socket->startListening();
	return server;
}

void ShitHTTP::HTTPServer::startHandlingRequests() {
	this->socket->handleRequests();
}
ShitHTTP::HTTPServer::HTTPServer(int osFlag,int port) {
	this->osFlag = osFlag;
	setFactory();
	std::cout << "CreatedServer\n";
	ISocket* socket = factory->openSocket(port);
	if (socket == nullptr) {
		std::cout << "Factory failed to open socket at port " << port << ".Exiting with code 0.\n";
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
		factory = (IFactory*) new ShitHTTP::WinFactory();
		break;
	default:
		exit(0);
	}
};

void ShitHTTP::HTTPServer::close() {
	this->socket->stop();
}

