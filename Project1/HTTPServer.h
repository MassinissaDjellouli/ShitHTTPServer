#pragma once
#include "WinFactory.h"
#include <iostream>

namespace ShitHTTP{
	class HTTPServer {
	public:
		static HTTPServer* create(int osFlag,int port);
		void startHandlingRequests();
		void close();
private:
	HTTPServer(int osFlag,int port);
	void setFactory();
	IFactory* factory;
	int osFlag;
	ISocket* socket;
	};
}