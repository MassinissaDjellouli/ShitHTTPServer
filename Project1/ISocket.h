#pragma once
#include <iostream>
#include "IHandler.h"
namespace ShitHTTP {
	class ISocket {
	public:
		virtual bool open() = 0;
		virtual bool startListening() = 0;
		virtual void handleRequests(IHandler* handler) = 0;
		virtual void stop() = 0;
		int getPort();
		ISocket(int port);
	protected:
		int port;
	};
}
