#include <ctime>
#include <thread>
#include "webc/webc.hpp"

using namespace std;
using namespace webc;
using namespace webc::server;
using namespace webc::utils;


//客户端请求线程处理
void request_thread(int client) {
	//创建一个请求
	request req = client;
}

//用于接受请求的线程
void accept_thread(bool *torun, long server) {
	//开始接受请求
	while (*torun)
	{
		sockaddr_in client_addr;
		socklen_t client_sock_size = sizeof(client_addr);
		int client = sock::accept_e(server, (sockaddr *)&client_addr, &client_sock_size);
		if (client == -1) continue;
		//开启线程进行处理
		std::thread m_thread(request_thread, client);
		m_thread.detach();
	}
}

//构造函数
httpserver::httpserver() {
	//端口
	try {
		int listen = config::get_config()["server"]["listen"].asInt();
		port = listen ? listen : 80;
	}
	catch (exception e) {
		port = 80;
	}
	//监听数
	try {
		int count = config::get_config()["server"]["listen_count"].asInt();
		listen_count = count ? count : 10;
	}
	catch (exception e) {
		listen_count = 10;
	}
}

//析构函数
httpserver::~httpserver() {

}

//创建服务器
state httpserver::create() {
	int _socket = sock::socket_e(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == -1) {
		sock::release_e();
		return socketnotcreate;
	}
	//地址处理
	sockaddr_in addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(port);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	//绑定地址
	if (-1 == sock::bind_e(_socket, (sockaddr*)&addrServ, sizeof(sockaddr_in))) {
		sock::close_r(_socket);
		return socketnotbind;
	}
	//开始监听
	if (-1 == sock::listen_e(_socket, listen_count)) {
		sock::close_r(_socket);
		return socketnotlisten;
	}
	this->server = _socket;
	return state::success;
}

//开启服务器
void httpserver::start() {
	std::time(&this->start_time);
	is_run = true;
	long _socket = this->server;
	torun = true;
	//开启线程进行处理
	std::thread m_thread(accept_thread, &torun, this->server);
	//m_thread.detach();
	m_thread.join();
}

//停止服务器
void httpserver::stop() {
	this->is_run = false;
}

//服务器是否在运行
bool httpserver::isrun() {
	return is_run;
}

//活动时间
long long httpserver::livetime() {
	time_t _time;
	std::time(&_time);
	return _time - start_time;
}