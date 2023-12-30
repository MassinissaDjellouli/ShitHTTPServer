#pragma once
#include "ISocket.h"
#include <iostream>
namespace ShitHTTP {
	class WinSocket:public ISocket {
	public:
		bool open();
		WinSocket(int port);
		int getPort();
	private:
		int port;
	};
}