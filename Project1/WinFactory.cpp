#include "WinFactory.h"

ShitHTTP::ISocket* ShitHTTP::WinFactory::openSocket(int port) {
	std::cout << "Factory Init\n";
	ISocket* socket = dynamic_cast<ISocket*>(new WinSocket(port));
	socket->open();
	return nullptr;
}