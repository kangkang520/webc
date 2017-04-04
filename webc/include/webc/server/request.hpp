#pragma once
#ifndef WEBC_SERVER_REQUEST_H
#define WEBC_SERVER_REQUEST_H

#include <iostream>

namespace webc {
	namespace server {
		class request {
		public:
			enum ERR {
				//body解析错误
				BODYERR = 1,
				//链接断开
				DISCONN = 2,
				//读取请求错误
				READERR = 3
			};

		public:
			//构造函数
			request(int);
			//获取url
			std::string url();
			//获取版本
			std::string version();
			//获取请求方式
			std::string method();
			//获取请求路径
			std::string path();
			//获取请求头
			std::string header(std::string key);
			//获取body
			template <typename T>
			T body(std::string);
			//获取请求数据
			template <typename T>
			T query(std::string);
			//获取文件
			template<typename T>
			T files(std::string);
		private:
			int read();
			bool continueread();
			void ondata(const char*, long);
			long client = -1;
			int err;
			//换行数
			long linec = 0;
			//上个字符是不是换行
			bool lastisbr = false;
			bool toreadbody = false;
			long long bodyread = 0;
			//数据存放
			std::string _url = "";
			std::string _version = "";
			std::string _method = "";
			std::string _path = "";
			std::map<std::string, std::string> _header;
			//body解析数据
			querystring body_str;
		};
	}
}

#endif // !WEBC_SERVER_REQUEST_H
