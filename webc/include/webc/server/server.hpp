#pragma once

#ifndef WEBC_SERVER_SERVER_H
#define WEBC_SERVER_SERVER_H

#include <iostream>

namespace webc {

	namespace server {

		enum state {
			success,			//成功
			socketnotcreate,	//没能创建socket
			socketnotbind,		//没能绑定socket
			socketnotlisten,	//没能监听
		};

		class httpserver {
		public:
			//构造函数
			httpserver();
			//析构函数
			~httpserver();
			//创建服务器
			state create();
			//开启服务器
			void start();
			//服务器是否在运行
			bool isrun();
			//停止服务器
			void stop();
			//服务器运行时间
			long long livetime();
		private:
			//启动时间
			time_t start_time;
			//是否允许
			bool is_run = false;
			//服务器配置
			int port = 80;
			int listen_count = 10;
			//服务器socket
			long server = -1;
			//是否需要运行
			bool torun = false;
		};

	}
}


#endif // !WEBC_SERVER_H
