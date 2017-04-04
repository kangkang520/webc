#pragma once
#ifndef WEBC_COMMON_ERROR_H
#define WEBC_COMMON_ERROR_H

#include <iostream>


namespace webc {
	class error :public std::exception {
	public:

		//���캯��
		error(std::string err, int code = 0, int other=0) {
			_err = err;
			_code = 0;
			_other = other;
		}

		//��ȡ������
		int code() {
			return _code;
		}

		//��ȡ������Ϣ
		std::string err() {
			return _err;
		}

		//����������Ϣ
		int other() {
			return _other;
		}

	private:
		std::string _err;
		int _code = 0;
		int _other = 0;
	};
}

#endif // !WEBC_COMMON_ERROR_H
