#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "webc/webc.hpp"

using namespace std;
using namespace webc::utils;
using namespace webc::utils::__loge;


Log *m_log;

Log::Log() {
	//��ǰʱ��
	std::string now = this->now("%Y_%m_%d.log");
	//��ȡ��־Ŀ¼
	std::string path = webc::server::config::get_config()["log"]["path"].asString();
	if (path.size() == 0) {
		clog << "��־���ò����ڣ���ʹ�á�./logs/����Ϊ��־Ŀ¼" << endl;
		path = "./logs/";
	}
	//ȷ����/����
	char last = path[path.size() - 1];
	this->filename = ((last == '/') || (last == '\\')) ? (path + now) : (path + "/" + now);
	//����Ŀ¼
	fs::mkdir_c(path);
}


Log Log::obj() {
	if (!m_log) {
		m_log = new Log();
	}
	return *m_log;
}

std::string Log::now(std::string format) {
	time_t now;
	time(&now);
	tm * _time = localtime(&now);
	char buffer[255];
	strftime(buffer, 255, format.c_str(), _time);
	return buffer;
}


Log& Log::operator<< (std::string& content) {
	std::string now = this->now("��%Y-%m-%d %M:%M:%S��");
	fs::append(this->filename, now + "\r\n" + content + "\r\n\r\n================\r\n");
	return *this;
}


Log& Log::operator<< (const char* str) {
	return *this << string(str);
}


Log& Log::operator<< (char* str) {
	return *this << string(str);
}


Log& Log::operator<< (long str) {
	return *this << "" + str;
}


Log& Log::operator<< (double str) {
	char buffer[50] = { 0 };
	sprintf(buffer, "%lf", str);
	return *this << string(buffer);
}


Log& Log::operator<< (char str){
	return *this << "" + str;
}

