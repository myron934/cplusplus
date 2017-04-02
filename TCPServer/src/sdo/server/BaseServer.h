/*
 * BaseServer.h
 *
 *  Created on: 2017年3月31日
 *      Author: weiminglun.myron
 */

#ifndef SDO_SERVER_BASESERVER_H_
#define SDO_SERVER_BASESERVER_H_
#include <sdo/net/IServer.h>
using sdo::net::IServer;
using sdo::net::IOServiceAgent;
using sdo::net::Connection;
namespace sdo {
namespace server {

class BaseServer: public IServer {
public:
    BaseServer(const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
    BaseServer(io_service& io_ser, const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
    virtual ~BaseServer(){};

    //override
    virtual size_t readProgressHandler(const char* data, size_t bytes);
    virtual void readCompleteHandler(boost::shared_ptr<Connection> conn, const char* data, size_t bytes);
    virtual void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec);
    virtual void connectionCompleteHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec);
};

} /* namespace server */
} /* namespace sdo */

#endif /* SDO_SERVER_BASESERVER_H_ */
