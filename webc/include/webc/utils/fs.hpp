#pragma once
#ifndef WEBC_UTILS_FS_H
#define WEBC_UTILS_FS_H

#include <iostream>

namespace webc {
	namespace utils{
		namespace fs {
			//����ļ�/Ŀ¼�Ƿ����
			bool exists(std::string);
			//�Ƿ���Ŀ¼
			bool isdir(std::string);
			//�ǲ����ļ�
			bool isfile(std::string);
			//����Ŀ¼
			bool mkdir(std::string);
			//ѭ������Ŀ¼
			bool mkdir_c(std::string);
			//д���ļ�������
			bool write_content(std::string, std::string);
			//��ȡ�ļ�
			std::string read_content(std::string);
			//׷���ļ�
			bool append(std::string, std::string);
		}
	}
}


#endif // !WEBC_UTILS_FS_H
