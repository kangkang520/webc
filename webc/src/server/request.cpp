#include "webc/webc.hpp"

using namespace std;
using namespace webc;
using namespace webc::server;
using namespace webc::utils;


#define strbeginwith(src, dest) (strncmp((src), (dest), strlen(dest)) == 0)

#define error_throw(err, type, other) (throw new error(err, type, other))

//构造函数
request::request(int client) {
	this->client = client;
	long long ret = this->read();
	if (ret > 0) {
		//读取完毕
		if (!this->body_str.parse()) {
			error_throw("无法解析body参数", BODYERR, 0);
		}
		sock::send_e(client, "OK", 2, 0);
		sock::close_e(client);
	}
	else if (ret == 0) {
		//客户的断开
		error_throw("浏览器已断开连接", DISCONN, 0);
	}
	else if (ret == -1) {
		//错误
		error_throw("请求数据读取错误", READERR, this->err);
	}
}

//获取url
std::string request::url() {
	return this->_url;
}

//获取版本
std::string request::version() {
	return this->_version;
}

//获取请求方式
std::string request::method() {
	return this->_method;
}

//获取请求路径
std::string request::path() {
	return this->_path;
}

//获取请求头
std::string request::header(std::string key) {
	return this->_header[key];
}

//获取body
template <typename T>
T request::body(std::string) {
}

//获取请求数据
template <typename T>
T request::query(std::string) {
}

//获取文件
template<typename T>
T request::files(std::string) {
}


//是否继续读取
bool request::continueread() {
	std::string len = this->_header["Content-Length"];
	//没有该字段
	if (len == "") {
		if (!toreadbody) return true;		//如果还没有开始读取body则继续读取
		return false;
	}
	long long ilen = atoll(len.c_str());
	//剩余长度大于现有长度
	if (ilen > bodyread) return true;
	return false;
}

//数据处理
void request::ondata(const char* data, long len) {
	const char *str = data;
	int bodyat = 0;
	//读取头
	if (!toreadbody) {
		for (int i = 0; i < len; i++) {
			if (data[i] == '\r') continue;
			else if (data[i] == '\n') {
				if (lastisbr) {
					//头部结束
					toreadbody = true;
					bodyat = i;
					break;
				}
				if (linec == 0) {
					//第一行
					char method[10] = { 0 };
					char path[20480] = { 0 };
					char version[30] = { 0 };
					sscanf(str, "%s %s %s", method, path, version);
					//对path以?分割
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
					//其他行
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
	//读取body
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
		//接收数据
		memset(buffer, 0, sizeof(buffer));
		len = sock::recv_e(client, buffer, buffer_read_size, 0);
		//检测
		if (len == SOCKET_ERROR) {
			//出错
#ifdef WIN32
			int err = GetLastError();
#else
			int err = errno;
#endif
			//出错
			this->err = err;
			return -1;
		}
		else if (len == 0) {
			//断开连接
			this->err = 0;
			return 0;
		}
		else {
			//数据处理
			total += len;
			this->ondata(buffer, len);
			//如果不需要再读取则退出循环
			if (!this->continueread()) break;
		}
	} while (len > 0);
	this->err = 0;
	return total;
}