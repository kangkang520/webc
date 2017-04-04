#pragma once
#ifndef WEBC_SERVER_REQUEST_H
#define WEBC_SERVER_REQUEST_H

#include <iostream>

namespace webc {
	namespace server {
		class request {
		public:
			enum ERR {
				//body��������
				BODYERR = 1,
				//���ӶϿ�
				DISCONN = 2,
				//��ȡ�������
				READERR = 3
			};

		public:
			//���캯��
			request(int);
			//��ȡurl
			std::string url();
			//��ȡ�汾
			std::string version();
			//��ȡ����ʽ
			std::string method();
			//��ȡ����·��
			std::string path();
			//��ȡ����ͷ
			std::string header(std::string key);
			//��ȡbody
			template <typename T>
			T body(std::string);
			//��ȡ��������
			template <typename T>
			T query(std::string);
			//��ȡ�ļ�
			template<typename T>
			T files(std::string);
		private:
			int read();
			bool continueread();
			void ondata(const char*, long);
			long client = -1;
			int err;
			//������
			long linec = 0;
			//�ϸ��ַ��ǲ��ǻ���
			bool lastisbr = false;
			bool toreadbody = false;
			long long bodyread = 0;
			//���ݴ��
			std::string _url = "";
			std::string _version = "";
			std::string _method = "";
			std::string _path = "";
			std::map<std::string, std::string> _header;
			//body��������
			querystring body_str;
		};
	}
}

#endif // !WEBC_SERVER_REQUEST_H
