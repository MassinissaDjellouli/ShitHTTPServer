#pragma once
#include "ISocket.h"
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
namespace ShitHTTP {
	class WinSocket:public ISocket {
	public:
		bool open();
		bool startListening();
		WinSocket(int port);
		int getPort();
		void handleRequests();
		void stop();
	private:
		SOCKET wsocket;
		SOCKET new_wsocket;
		WSADATA wsa_data;
		struct sockaddr_in server;
		int server_len;
		static const int BUFFER_SIZE = 30720;
		int port;
		bool active = true;
	};
}