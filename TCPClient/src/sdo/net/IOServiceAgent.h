/*
 * IOServiceAgent.h
 *
 *  Created on: 2017年1月20日
 *      Author: myron
 */

#ifndef IOSERVICEAGENT_H_
#define IOSERVICEAGENT_H_

#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
namespace sdo {
namespace net {

/**
 * 这个类用来生成io_service, 并指定用几个线程来跑io_service业务.
 * 首先调用构造函数创建实例， 然后调用init初始化.
 * 最后调用getIOService获取io_service
 */
class IOServiceAgent: boost::noncopyable{
public:
	IOServiceAgent();
	IOServiceAgent(unsigned int thread_num, unsigned int service_mod);
	~IOServiceAgent();
	int init(unsigned int thread_num=1, unsigned int service_mod=5);
	boost::asio::io_service& getIOService();
private:
	unsigned int thread_num_;
	unsigned int service_mod_;//一个service跑几个线程
	boost::asio::io_service* io_services_;//io_services数组
	std::vector<boost::asio::io_service::work*> works_; //work数组, 每个io_service有一个,防止io_service空闲停止
	boost::thread_group threads_;//线程组
	std::size_t io_service_num_; //io_service_num总数
	unsigned int io_service_counter_; //当前指向的io_service下表, getIOService()函数轮循取io_service时用到
};
} /* namespace sdo */
} /* namespace com */
#endif /* IOSERVICEAGENT_H_ */
