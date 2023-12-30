#include "WinFactory.h"

ShitHTTP::ISocket* ShitHTTP::WinFactory::openSocket(int port) {
	std::cout << "Factory Init\n";
	ISocket* socket = dynamic_cast<ISocket*>(new WinSocket(port));
	if (!socket->open()) {
		std::cout << "Socket could not open. \n";
		return nullptr;
	};
	return socket;
}