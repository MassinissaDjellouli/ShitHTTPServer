#include "HTTPServer.h"

ShitHTTP::HTTPServer* ShitHTTP::HTTPServer::create(int osFlag) {
	return new ShitHTTP::HTTPServer(osFlag);
}

ShitHTTP::HTTPServer::HTTPServer(int osFlag) {
	this->osFlag = osFlag;
	setFactory();
	std::cout << "CreatedServer\n";
	factory->openSocket(80);
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

