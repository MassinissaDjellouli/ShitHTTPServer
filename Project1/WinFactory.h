#pragma once
#include "WinSocket.h"
#include "IFactory.h"
#include <iostream>
namespace ShitHTTP {
	class WinFactory:IFactory{
	public:
		ISocket* openSocket(int port);
	};
}

