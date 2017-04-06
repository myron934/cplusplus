//============================================================================
// Name        : TCPClient.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <sdo/log/LogHelper.h>
#include <sdo/net/Connection.h>
#include <sdo/net/IOServiceAgent.h>
#include <sdo/protobuf/header.pb.h>
using namespace std;
using namespace sdo::net;
size_t readProgressHandler(const char* data, size_t bytes) {
    if(bytes<sizeof(int)) return sizeof(int)-bytes;
    int len=ntohl(*(const int*)data);
    return len-bytes;
}

void readCompleteHandler(boost::shared_ptr<Connection> conn,
        const char* data, size_t bytes) {
    LOG_ENTER_FUNCTION
    int len=ntohl(*(const int*)data);
    //心跳包, 直接放过
    if(sizeof(int)==len) return;
    boost::shared_ptr<sdo::protobuf::header> h(new sdo::protobuf::header);
    if (!h->ParseFromArray(data+sizeof(int),bytes-sizeof(int))) {
        //TODO:解析包头失败,记录个日志吧
        return;
    }
    std::cout<<h->method()<<std::endl;
}

void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){
    LOG_ENTER_FUNCTION
    string data="connection closed\ntry to reconnect\n";
    cout<<data<<endl;
    boost::this_thread::sleep(boost::posix_time::seconds(3));
    conn->asyncReConnect(1000);
}

void connectionCompleteHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){
    LOG_ENTER_FUNCTION
    if(ec){
        std::cout<<"value:"<<ec.value()<<" msg:"<<ec.message()<<std::endl;
        return;
    }
    sdo::protobuf::header h;
    h.set_method("sdo/getinfo");
    sdo::protobuf::header data;
    data.set_method("this is body");
    h.set_body(data.SerializeAsString());
    int len=htonl(h.ByteSize()+sizeof(int));
    boost::asio::streambuf buf;
    ostream os(&buf);
    os.write((char*)&len,sizeof(int));
    os<<h.SerializeAsString();
    conn->doWrite(buf);
}

int main() {
    boost::shared_ptr<IOServiceAgent> io_agent(new IOServiceAgent);
    io_agent->init(1,5);
    boost::shared_ptr<Connection> conn=Connection::newInstance(0,'c',io_agent->getIOService(),5000);
    conn->setConnectionCompleteHandler(boost::bind(connectionCompleteHandler,_1,_2));
    conn->setConnectionClosedHandler(boost::bind(connectionCloseHandler,_1,_2));
    conn->setReadProcessHandler(boost::bind(readProgressHandler,_1,_2));
    conn->setReadCompleteHandler(boost::bind(readCompleteHandler,_1,_2,_3));
    boost::shared_ptr<boost::asio::streambuf> sb(new boost::asio::streambuf);
    std::ostream os(sb.get());
    int len=htonl(sizeof(int));
    os.write((char*)&len,sizeof(int));
    conn->setHeartPacket(sb);
//    conn->asyncConnect("www.baidu.com","https",1000);
    conn->asyncConnect("127.0.0.1",8081,1000);
    io_agent->joinAll();
    return 0;
}
