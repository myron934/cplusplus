/*
 * ProtoBufServer.cpp
 *
 *  Created on: 2017年4月5日
 *      Author: weiminglun.myron
 */

#include <sdo/server/ProtoBufServer.h>
#include <sdo/log/LogHelper.h>
#include <sdo/protobuf/header.pb.h>
#include <sdo/server/ProtoDecoder.h>
namespace sdo {
namespace server {

ProtoBufServer::ProtoBufServer(const boost::shared_ptr<IOServiceAgent>& io_agent,
        unsigned int port, int time_out_millisec) :
        IServer(io_agent, port, time_out_millisec) {
//    对于服务端来说,不设置心跳包也是可以的
    boost::shared_ptr<streambuf> sb(new streambuf);
    std::ostream os(sb.get());
    int len=0;
    os.write((char*)&len,sizeof(int));
    setHeartPacket(sb);
}

ProtoBufServer::ProtoBufServer(io_service& io_ser,
        const boost::shared_ptr<IOServiceAgent>& io_agent, unsigned int port,
        int time_out_millisec) :
        IServer(io_ser, io_agent, port, time_out_millisec) {
    //    对于服务端来说,不设置心跳包也是可以的
    boost::shared_ptr<streambuf> sb(new streambuf);
    std::ostream os(sb.get());
    int len=0;
    os.write((char*)&len,sizeof(int));
    setHeartPacket(sb);
}

size_t ProtoBufServer::readProgressHandler(const char* data, size_t bytes) {
    if(bytes<sizeof(int)) return sizeof(int)-bytes;
    int len=ntohl(*(const int*)data);
    return len-bytes;
}

void ProtoBufServer::readCompleteHandler(boost::shared_ptr<Connection> conn,
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
    sdo::protobuf::header body;
    body.ParseFromString(h->body());
    std::cout<<body.method()<<std::endl;

}

void ProtoBufServer::connectionCloseHandler(boost::shared_ptr<Connection> conn,
        const boost::system::error_code& ec) {
    LOG_ENTER_FUNCTION
}

void ProtoBufServer::connectionCompleteHandler(
        boost::shared_ptr<Connection> conn,
        const boost::system::error_code& ec) {
}

} /* namespace server */
} /* namespace sdo */
