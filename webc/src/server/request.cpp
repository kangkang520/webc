#include "webc/webc.hpp"

using namespace std;
using namespace webc;
using namespace webc::server;
using namespace webc::utils;


#define strbeginwith(src, dest) (strncmp((src), (dest), strlen(dest)) == 0)

#define error_throw(err, type, other) (throw new error(err, type, other))

//���캯��
request::request(int client) {
	this->client = client;
	long long ret = this->read();
	if (ret > 0) {
		//��ȡ���
		if (!this->body_str.parse()) {
			error_throw("�޷�����body����", BODYERR, 0);
		}
		sock::send_e(client, "OK", 2, 0);
		sock::close_e(client);
	}
	else if (ret == 0) {
		//�ͻ��ĶϿ�
		error_throw("������ѶϿ�����", DISCONN, 0);
	}
	else if (ret == -1) {
		//����
		error_throw("�������ݶ�ȡ����", READERR, this->err);
	}
}

//��ȡurl
std::string request::url() {
	return this->_url;
}

//��ȡ�汾
std::string request::version() {
	return this->_version;
}

//��ȡ����ʽ
std::string request::method() {
	return this->_method;
}

//��ȡ����·��
std::string request::path() {
	return this->_path;
}

//��ȡ����ͷ
std::string request::header(std::string key) {
	return this->_header[key];
}

//��ȡbody
template <typename T>
T request::body(std::string) {
}

//��ȡ��������
template <typename T>
T request::query(std::string) {
}

//��ȡ�ļ�
template<typename T>
T request::files(std::string) {
}


//�Ƿ������ȡ
bool request::continueread() {
	std::string len = this->_header["Content-Length"];
	//û�и��ֶ�
	if (len == "") {
		if (!toreadbody) return true;		//�����û�п�ʼ��ȡbody�������ȡ
		return false;
	}
	long long ilen = atoll(len.c_str());
	//ʣ�೤�ȴ������г���
	if (ilen > bodyread) return true;
	return false;
}

//���ݴ���
void request::ondata(const char* data, long len) {
	const char *str = data;
	int bodyat = 0;
	//��ȡͷ
	if (!toreadbody) {
		for (int i = 0; i < len; i++) {
			if (data[i] == '\r') continue;
			else if (data[i] == '\n') {
				if (lastisbr) {
					//ͷ������
					toreadbody = true;
					bodyat = i;
					break;
				}
				if (linec == 0) {
					//��һ��
					char method[10] = { 0 };
					char path[20480] = { 0 };
					char version[30] = { 0 };
					sscanf(str, "%s %s %s", method, path, version);
					//��path��?�ָ�
					this->_method = method;
					this->_version = version;
					for (int j = 0; j < strlen(path); j++) {
						if (path[j] == '?') {
							this->_url = std::string(path, j);
							this->_path = path + j + 1;
						}
					}
				}
				else {
					//������
					char key[512] = { 0 };
					char value[51200] = { 0 };
					sscanf(str, "%s %s", key, value);
					key[strlen(key) - 1] = 0;
					this->_header[key] = value;
				}
				str = data + i + 1;
				lastisbr = true;
				linec++;
			}
			else {
				lastisbr = false;
			}
		}
	}
	//��ȡbody
	if (toreadbody && bodyat < len - 1) {
		this->bodyread = len - bodyat;
		const char * body = data + bodyat;
		if (strbeginwith(this->_header["Content-Type"].c_str(), "multipart/form-data")) {
			cout << "formdata" << endl;
		}
		else if (strbeginwith(this->_header["Content-Type"].c_str(), "application/x-www-form-urlencoded")) {
			this->body_str.append(body);
		}
		else {
			cout << "other" << endl;
		}
	}
}

int request::read() {
	const int buffer_read_size = 40960;
	int len = 0;
	int total = 0;
	char buffer[buffer_read_size];
	do {
		//��������
		memset(buffer, 0, sizeof(buffer));
		len = sock::recv_e(client, buffer, buffer_read_size, 0);
		//���
		if (len == SOCKET_ERROR) {
			//����
#ifdef WIN32
			int err = GetLastError();
#else
			int err = errno;
#endif
			//����
			this->err = err;
			return -1;
		}
		else if (len == 0) {
			//�Ͽ�����
			this->err = 0;
			return 0;
		}
		else {
			//���ݴ���
			total += len;
			this->ondata(buffer, len);
			//�������Ҫ�ٶ�ȡ���˳�ѭ��
			if (!this->continueread()) break;
		}
	} while (len > 0);
	this->err = 0;
	return total;
}