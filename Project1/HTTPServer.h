#pragma once
#include "WinFactory.h"
#include <iostream>

namespace ShitHTTP{
	class HTTPServer {
	public:
		static HTTPServer* create(int osFlag);
private:
	HTTPServer(int osFlag);
	void setFactory();
	IFactory* factory;
	int osFlag;
	};
}