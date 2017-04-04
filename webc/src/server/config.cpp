#include "webc/webc.hpp"

using namespace std;
using namespace webc::server;
using namespace webc::utils;

json::Value value = NULL;

json::Value config::get_config(std::string filepath) {
	if (value != NULL)
		return value;
	//��ȡ�����ļ�����
	std::string json_str = fs::read_content(filepath);
	if (json_str == "") {
		std::cerr << "��ȡ�����ļ������޷���ȡ���������ļ������ڻ�ռ�ã�" << endl;
		throw new exception("��ȡ�����ļ������޷���ȡ���������ļ������ڻ�ռ�ã�");
		return NULL;
	}
	//����jeson
	json::Reader reader;
	if (!reader.parse(json_str, value))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cerr << "��ȡ�����ļ�����(�޷��������������﷨����)" << endl;
		throw new exception("��ȡ�����ļ�����(�޷��������������﷨����)");
		return NULL;
	}
	std::clog << "�����Ѽ���" << std::endl;
	//��������
	return value;
}