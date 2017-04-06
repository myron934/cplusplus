/*
 * ProtoBufServer.h
 *
 *  Created on: 2017年4月5日
 *      Author: weiminglun.myron
 */

#ifndef SDO_SERVER_PROTOBUFSERVER_H_
#define SDO_SERVER_PROTOBUFSERVER_H_
#include <sdo/net/IServer.h>
using sdo::net::IServer;
using sdo::net::IOServiceAgent;
using sdo::net::Connection;
namespace sdo {
namespace server {

/**
 * 这是一个基于protocol buffer协议的server
 * 数据包协议格式为: [包长(4字节整数)][包头包体(sdo::protobf::header)]
 */
class ProtoBufServer: public IServer {

public:
    ProtoBufServer(const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
    ProtoBufServer(io_service& io_ser, const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
    virtual ~ProtoBufServer(){}
    //override
   virtual size_t readProgressHandler(const char* data, size_t bytes);
   virtual void readCompleteHandler(boost::shared_ptr<Connection> conn, const char* data, size_t bytes);
   virtual void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec);
   virtual void connectionCompleteHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec);
};

} /* namespace server */
} /* namespace sdo */

#endif /* SDO_SERVER_PROTOBUFSERVER_H_ */
