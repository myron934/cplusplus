/*
 * BaseServer.h
 *
 *  Created on: 2017年3月31日
 *      Author: weiminglun.myron
 */

#ifndef SDO_EXAMPLES_BASESERVER_H_
#define SDO_EXAMPLES_BASESERVER_H_
#include <sdo/net/IServer.h>
using sdo::net::IServer;
using sdo::net::IOServiceAgent;
using sdo::net::Connection;
namespace sdo {
namespace server {
/**
 * 一个简单的协议, 以\n结尾的字符串作为一个完整的数据包
 * 如果需要实现其他协议, 只需要重写
 * readProgressHandler, readCompleteHandler, connectionCloseHandler, connectionCompleteHandler
 * 这四个方法
 */
class BaseServer: public IServer {
public:
    BaseServer(const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
    BaseServer(io_service& io_ser, const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
    virtual ~BaseServer(){};

//    @override
    virtual size_t readProgressHandler(const char* data, size_t bytes);
    virtual void readCompleteHandler(boost::shared_ptr<Connection> conn, const char* data, size_t bytes);
    virtual void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec);
    virtual void connectionCompleteHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec);
};

} /* namespace server */
} /* namespace sdo */

#endif /* SDO_EXAMPLES_BASESERVER_H_ */
