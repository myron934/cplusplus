/*
 * ServerConnection.h
 *
 *  Created on: 2017年1月30日
 *      Author: myron
 */

#ifndef SERVERCONNECTION_H_
#define SERVERCONNECTION_H_
#include "IConnection.h"
namespace com {
namespace sdo {
/**
 * 服务器端连接。遵从 接收请求->响应请求 的形式， 接收与响应成对出现。
 * 继承自IConnection， 重载了start, doRead, onCheckPing函数
 * 启动后自动准备读取客户端数据。接收到数据后，调用处理函数。处理完以后服务器再次等待读取客户端请求
 *
 * 使用步骤： 1调用newInstance(); 2调用acceptor.accept()与客户端成功建立连接后调用start()函数启动.
 */
class ServerConnection :public IConnection{
public:

	virtual ~ServerConnection(){};
	static boost::shared_ptr<ServerConnection> newInstance(int id,io_service& service,unsigned int time_out_sec=10000);
protected:
	ServerConnection(int id,io_service& service,unsigned int time_out_sec=10000):IConnection(id,'s',service,time_out_sec){};
	virtual void onCheckPing(const boost::system::error_code& err);
	virtual size_t readProgress(const boost::system::error_code& err, size_t bytes);
};

} /* namespace sdo */
} /* namespace com */

#endif /* SERVERCONNECTION_H_ */
