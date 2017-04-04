//============================================================================
// Name        : TCPClient.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <sdo/net/Connection.h>
#include <sdo/net/IOServiceAgent.h>
#include <sdo/log/LogHelper.h>
using namespace std;
using namespace sdo::net;
size_t readProgressHandler(const char* data, size_t bytes) {
//    LOG_ENTER_FUNCTION
    bool found = std::find(data, data + bytes, '\n') < data + bytes;
    // we read one-by-one until we get to enter, no buffering
    return found ? 0 : 1;
}

void readCompleteHandler(boost::shared_ptr<Connection> conn,
        const char* data, size_t bytes) {
    LOG_ENTER_FUNCTION
    std::stringstream ss;
    ss.write(data,bytes);
    std::string str;
    str=ss.str();
    std::cout<<"receive a message from server："<<str<<std::endl;
}

void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){
    LOG_ENTER_FUNCTION
    string data="connection closed\n";
    cout<<data<<endl;
};

void connectionCompleteHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){
    LOG_ENTER_FUNCTION
    if(ec){
        std::cout<<"value:"<<ec.value()<<"msg:"<<ec.message()<<std::endl;
        return;
    }
    string data="hello server\n";
    conn->doWrite(data.c_str(),data.length());
};

int main() {
    boost::shared_ptr<IOServiceAgent> io_agent(new IOServiceAgent);
    io_agent->init(1,5);
    boost::shared_ptr<Connection> conn=Connection::newInstance(0,'c',io_agent->getIOService(),2000);
    conn->setConnectionCompleteHandler(boost::bind(connectionCompleteHandler,_1,_2));
    conn->setConnectionClosedHandler(boost::bind(connectionCloseHandler,_1,_2));
    conn->setReadProcessHandler(boost::bind(readProgressHandler,_1,_2));
    conn->setReadCompleteHandler(boost::bind(readCompleteHandler,_1,_2,_3));
    boost::shared_ptr<boost::asio::streambuf> sb(new boost::asio::streambuf);
    std::ostream os(sb.get());
    os << "heart\n";
    conn->setHeartPacket(sb);
    conn->asyncConnect("127.0.0.1",8081,1000);
    io_agent->joinAll();
	return 0;
}
