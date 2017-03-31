//============================================================================
// Name        : TCPServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "Connection.h"
#include "IOServiceAgent.h"
#include "IServer.h"
using namespace std;
using namespace com::sdo::net;
using namespace com::sdo;
int main() {
	boost::shared_ptr<IOServiceAgent> io_agent(new IOServiceAgent);
	io_agent->init(5,5);
	io_service io_ser;
	IServer server(io_ser,io_agent,6789);
	server.start();
	io_ser.run();
//	while(true){
//
//	}
	return 0;
}
