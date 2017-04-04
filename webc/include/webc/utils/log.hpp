#pragma once

#ifndef WEBC_UTILS_LOG_H
#define WEBC_UTILS_LOG_H

#include <iostream>
#include <ctime>

namespace webc {

	namespace utils {

		namespace __loge {

			class Log {
			public:
				//获取日志对象
				static Log obj();
				//写入日志
				Log& operator<< (std::string&);
				Log& operator<< (const char*);
				Log& operator<< (char*);
				Log& operator<< (long);
				Log& operator<< (double);
				Log& operator<< (char);
			private:
				Log();
				std::string now(std::string);
				std::string filename;
			};

		}

		typedef __loge::Log __log;

#define flog __log::obj()
	}

}



#endif // !WEBC_UTILS_LOG_H
