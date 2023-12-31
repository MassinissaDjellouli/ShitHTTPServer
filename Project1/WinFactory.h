#pragma once
#include "WinSocket.h"
#include "IFactory.h"
#include <iostream>
namespace ShitHTTP {
	class WinFactory:public IFactory{
	public:
		ISocket* openSocket(int port);
	};
}

