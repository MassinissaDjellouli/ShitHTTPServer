#pragma once
#include <iostream>
namespace ShitHTTP {
	class ISocket {
	public:
		virtual bool open() = 0;
		int getPort();
		ISocket(int port);
	protected:
		int port;
	};
}
