#pragma once
#include "WinFactory.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include "WebServerHandler.h"
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
	std::string dir;
	ISocket* socket;
	IHandler* handler;
	std::unordered_map<std::string, IHandler*> handlers;
	std::unordered_map<std::string, IHandler*> getDefaultHandlers();
	std::unordered_map<std::string,std::string> readConfigFile();
	};
}