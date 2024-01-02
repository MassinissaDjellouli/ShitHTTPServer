#include "WinSocket.h"
bool ShitHTTP::WinSocket::open(){
	std::cout << "PORT " << getPort()<< "\n";
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
		std::cout << "wsa init failed \n";
		return false;
	}
	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET) {
		std::cout << "Invalid socket returned.\n";
		return false;
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(port);
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, server_len) != 0) {
		std::cout << "Could not bind socket at port " << port << ".\n";
		return false;
	}
	std::cout << "Socket opened and bound to port " << port << ". Ready to listen.\n";
	return true;
}
int ShitHTTP::WinSocket::getPort() {
	return this->port;
}
ShitHTTP::WinSocket::WinSocket(int port):ISocket(port){
	std::cout << "WinSocket Created \n";
	this->port = port;
}
bool ShitHTTP::WinSocket::startListening() {
	if (listen(wsocket, 20) != 0) {
		std::cout << "Could not listen on port " << port << ".\n";
		return false;
	}
	std::cout << "Listening on port " << port << ".\n";
	return true;
}

void ShitHTTP::WinSocket::stop() {
	active = false;
}

void ShitHTTP::WinSocket::handleRequests(IHandler* handler) {
	int bytesReceived;
	while (active) {
		new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
		if (new_wsocket == INVALID_SOCKET) {
			std::cout << "Could not accept a request.\n";
			continue;
		}

		char buff[BUFFER_SIZE] = { 0 }; 
		bytesReceived = recv(new_wsocket, buff, BUFFER_SIZE, 0);
		if (bytesReceived < 0) {
			std::cout << "Could not read client request. \n";
			continue;
		}
		
		std::string msg = handler->handle(buff);

		int bytesSent = 0;
		int totalBytesSent = 0;
		while (totalBytesSent < msg.size()) {
			bytesSent = send(new_wsocket, msg.c_str(), msg.size(), 0);
			if (bytesSent < 0) {
				std::cout << "An error occurend when trying to send bytes\n";
			}
			totalBytesSent += bytesSent;
		}
		closesocket(new_wsocket);
	}
	closesocket(wsocket);
	WSACleanup();
}