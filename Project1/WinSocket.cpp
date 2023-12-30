#include "WinSocket.h"
bool ShitHTTP::WinSocket::open(){
	std::cout << "PORT " << getPort()<< "\n";
	return false;
}
int ShitHTTP::WinSocket::getPort() {
	return this->port;
}
ShitHTTP::WinSocket::WinSocket(int port):ISocket(port){
	std::cout << "WinSocket Created \n";
	this->port = port;
}
