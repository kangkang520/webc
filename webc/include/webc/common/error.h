#pragma once
#ifndef WEBC_COMMON_ERROR_H
#define WEBC_COMMON_ERROR_H

#include <iostream>


namespace webc {
	class error :public std::exception {
	public:

		//构造函数
		error(std::string err, int code = 0, int other=0) {
			_err = err;
			_code = 0;
			_other = other;
		}

		//获取错误码
		int code() {
			return _code;
		}

		//获取错误信息
		std::string err() {
			return _err;
		}

		//返回其他信息
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
