#pragma once
#ifndef WEBC_UTILS_FS_H
#define WEBC_UTILS_FS_H

#include <iostream>

namespace webc {
	namespace utils{
		namespace fs {
			//检测文件/目录是否存在
			bool exists(std::string);
			//是否是目录
			bool isdir(std::string);
			//是不是文件
			bool isfile(std::string);
			//创建目录
			bool mkdir(std::string);
			//循环创建目录
			bool mkdir_c(std::string);
			//写入文件并覆盖
			bool write_content(std::string, std::string);
			//读取文件
			std::string read_content(std::string);
			//追加文件
			bool append(std::string, std::string);
		}
	}
}


#endif // !WEBC_UTILS_FS_H
