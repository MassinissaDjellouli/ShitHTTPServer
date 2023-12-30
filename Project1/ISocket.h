#pragma once
#include <iostream>

namespace ShitHTTP {
	class ISocket {
	public:
		virtual bool open() = 0;
		virtual bool startListening() = 0;
		virtual void handleRequests() = 0;
		virtual void stop() = 0;
		int getPort();
		ISocket(int port);
	protected:
		int port;
	};
}
