#include <ctime>
#include <thread>
#include "webc/webc.hpp"

using namespace std;
using namespace webc;
using namespace webc::server;
using namespace webc::utils;


//�ͻ��������̴߳���
void request_thread(int client) {
	//����һ������
	request req = client;
}

//���ڽ���������߳�
void accept_thread(bool *torun, long server) {
	//��ʼ��������
	while (*torun)
	{
		sockaddr_in client_addr;
		socklen_t client_sock_size = sizeof(client_addr);
		int client = sock::accept_e(server, (sockaddr *)&client_addr, &client_sock_size);
		if (client == -1) continue;
		//�����߳̽��д���
		std::thread m_thread(request_thread, client);
		m_thread.detach();
	}
}

//���캯��
httpserver::httpserver() {
	//�˿�
	try {
		int listen = config::get_config()["server"]["listen"].asInt();
		port = listen ? listen : 80;
	}
	catch (exception e) {
		port = 80;
	}
	//������
	try {
		int count = config::get_config()["server"]["listen_count"].asInt();
		listen_count = count ? count : 10;
	}
	catch (exception e) {
		listen_count = 10;
	}
}

//��������
httpserver::~httpserver() {

}

//����������
state httpserver::create() {
	int _socket = sock::socket_e(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == -1) {
		sock::release_e();
		return socketnotcreate;
	}
	//��ַ����
	sockaddr_in addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(port);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	//�󶨵�ַ
	if (-1 == sock::bind_e(_socket, (sockaddr*)&addrServ, sizeof(sockaddr_in))) {
		sock::close_r(_socket);
		return socketnotbind;
	}
	//��ʼ����
	if (-1 == sock::listen_e(_socket, listen_count)) {
		sock::close_r(_socket);
		return socketnotlisten;
	}
	this->server = _socket;
	return state::success;
}

//����������
void httpserver::start() {
	std::time(&this->start_time);
	is_run = true;
	long _socket = this->server;
	torun = true;
	//�����߳̽��д���
	std::thread m_thread(accept_thread, &torun, this->server);
	//m_thread.detach();
	m_thread.join();
}

//ֹͣ������
void httpserver::stop() {
	this->is_run = false;
}

//�������Ƿ�������
bool httpserver::isrun() {
	return is_run;
}

//�ʱ��
long long httpserver::livetime() {
	time_t _time;
	std::time(&_time);
	return _time - start_time;
}