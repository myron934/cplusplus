/*
 * ClientConnection.h
 *
 *  Created on: 2017年1月30日
 *      Author: myron
 */

#ifndef CLIENTCONNECTION_H_
#define CLIENTCONNECTION_H_
#include "IConnection.h"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
namespace com {
namespace sdo {
/**
 * 客户端连接。遵从 发送请求->接收响应 的形式， 发送与接收成对出现。
 * 注意，如果一次doWrite()发送了多个数据包，默认只会doRead一次，接收一次服务器响应。如果需要接收多次服务器响应，手动调用doRead
 * 继承自IConnection， 重载了start, doWrite, onCheckPing函数
 *
 * 使用步骤： 1调用newInstance(); 2调用connect()连接到服务器后，调用start()函数启动.
 */
class ClientConnection : public IConnection{
public:
	virtual ~ClientConnection(){};
//	virtual void start();
	virtual int connect(ip::tcp::endpoint& ep);
	virtual int connect();
	virtual void doWrite(const char* buffer, size_t bytes);
	virtual void onRead(const boost::system::error_code& err, size_t bytes);
	static boost::shared_ptr<ClientConnection> newInstance(int id,io_service& service,unsigned int time_out_sec=10000);
protected:
	ClientConnection(int id,io_service& service,unsigned int time_out_sec=10000):IConnection(id,'c',service,time_out_sec){};
	virtual void onCheckPing(const boost::system::error_code& err);
	virtual void onWrite(const boost::system::error_code& err, size_t bytes);
private:
	ip::tcp::endpoint ep_;
};

} /* namespace sdo */
} /* namespace com */

#endif /* CLIENTCONNECTION_H_ */
