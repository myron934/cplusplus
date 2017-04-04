/*
 * IOServiceAgent.cpp
 *
 *  Created on: 2017年1月20日
 *      Author: myron
 */
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <sdo/net/IOServiceAgent.h>

using namespace boost::asio;
namespace sdo {
namespace net {
/**
 * 默认创建1个线程跑业务
 */
IOServiceAgent::IOServiceAgent():thread_num_(1),service_mod_(5),io_services_(NULL),io_service_num_(0),io_service_counter_(0) {
}
/**
 *@param thread_num thread_num>0. 指定多少个线程跑业务
 *@param serviece_mod 一个service跑几个线程, 确定了创建几个io_service
 */
IOServiceAgent::IOServiceAgent(unsigned int thread_num, unsigned int service_mod) {
	init(thread_num,service_mod);
}


IOServiceAgent::~IOServiceAgent() {
    threads_.interrupt_all();
	for(int i=io_service_num_-1;i>=0;--i){
		io_services_[i].stop();
		delete works_[i];
	}
	delete[] io_services_;
}

/**
 * 初始化, 创建io_service, 初始化线程等
 * @return 成功返回0 否则返回-1
 */
int IOServiceAgent::init(unsigned int thread_num, unsigned int service_mod) {
	io_service_counter_=0;
	thread_num_=thread_num==0?1:thread_num;
	service_mod_=service_mod;
	io_service_num_=thread_num_%service_mod_==0? thread_num_/service_mod_:thread_num_/service_mod_+1;
	io_services_=new io_service[io_service_num_];
	if(NULL==io_services_) return -1;
	unsigned int thread_num_running=0;
	for(unsigned int i=0;i<io_service_num_;++i){
		for(int j=service_mod_;j>0;--j){
			if(thread_num_<(++thread_num_running)) break;
			io_service::work* work(new io_service::work(io_services_[i]));
			if(NULL==work) return -1;
			works_.push_back(work);
			boost::system::error_code ec;
			threads_.create_thread(boost::bind(&io_service::run,&io_services_[i],ec));
			if(ec) return -1;
		}
	}

	return 0;
}

void IOServiceAgent::joinAll() {
    if(threads_.size()>0)
        threads_.join_all();
}

/**
 * 获取一个io_service. 如果有多个io_service,则采用轮循的方式取
 * @return io_service的引用
 */
boost::asio::io_service& IOServiceAgent::getIOService() {
	io_service &service=io_services_[io_service_counter_++];
	if(io_service_counter_>=io_service_num_) io_service_counter_=0;
	return service;
}
} /* namespace sdo */
} /* namespace com */


