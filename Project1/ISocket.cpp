#include "ISocket.h"
int ShitHTTP::ISocket::getPort() {
			return port;
}
ShitHTTP::ISocket::ISocket(int port) {
	this->port = port;
}

