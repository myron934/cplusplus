/*
 * BaseServer.cpp
 *
 *  Created on: 2017年3月31日
 *      Author: weiminglun.myron
 */

#include <sdo/server/BaseServer.h>
#include <sstream>
#include <iostream>
namespace sdo {
namespace server {

BaseServer::BaseServer(const boost::shared_ptr<IOServiceAgent>& io_agent,
        unsigned int port, int time_out_millisec) :
        IServer(io_agent, port, time_out_millisec) {
//    对于服务端来说,不设置心跳包也是可以的
    boost::shared_ptr<streambuf> sb(new streambuf);
    std::ostream os(sb.get());
    os << '\n';
    setHeartPacket(sb);
}

BaseServer::BaseServer(io_service& io_ser,
        const boost::shared_ptr<IOServiceAgent>& io_agent, unsigned int port,
        int time_out_millisec) :
        IServer(io_ser, io_agent, port, time_out_millisec) {
    //    对于服务端来说,不设置心跳包也是可以的
    boost::shared_ptr<streambuf> sb(new streambuf);
    std::ostream os(sb.get());
    os << '\n';
    setHeartPacket(sb);
}


/**
 * 用于判断是否读到一个完整的数据包
 *@param data 目前读取到的数据
 *@param bytes 目前读取到的数据长度
 *@return data's length that need to read left
 */
size_t BaseServer::readProgressHandler(const char* data, size_t bytes) {
    bool found = std::find(data, data + bytes, '\n') < data + bytes;
    // we read one-by-one until we get to enter, no buffering
    return found ? 0 : 1;
}

/**
 * 读取到完整包数据后回调的处理函数. 当然, 如果读取到一个错误的包,也要在此处理
 *@param conn 当前链接
 *@param 包数据
 *@param 数据长度
 */
void BaseServer::readCompleteHandler(boost::shared_ptr<Connection> conn,
        const char* data, size_t bytes) {
    std::stringstream ss;
    ss.write(data,bytes);
    std::string str;
    str=ss.str();
    std::cout<<"receive a message from client："<<str<<std::endl;
}

/**
 * 链接被关闭时触发
 */
void BaseServer::connectionCloseHandler(boost::shared_ptr<Connection> conn,
        const boost::system::error_code& ec) {
    std::cout<<"connection was closed："<<ec.message()<<std::endl;
}

/**
 * 建立链接成功后触发. 只有在客户端链接的时候回用到.因此服务端可以不做实现
 */
void BaseServer::connectionCompleteHandler(boost::shared_ptr<Connection> conn,
        const boost::system::error_code& ec) {
}

} /* namespace server */
} /* namespace sdo */
