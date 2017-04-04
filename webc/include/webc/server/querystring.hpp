#pragma once
#ifndef WEBC_UTILS_QUERYSTRING_H
#define WEBC_UTILS_QUERYSTRING_H

#include <iostream>
#include "../common/any.hpp"


namespace webc {
	namespace server {
		class querystring {
		public:
			//构造函数
			querystring(std::string str);
			querystring();
			void append(std::string str);
			bool parse();
			//获取一个元素
			template <typename T>
			T& get(std::string key) {
				return m_map[key].cast<T>();
			}
		private:
			std::map<std::string, webc::any> m_map;
			std::string str = "";
			//天假一个key
			void add(std::string, std::string);
		};
	}
}

#endif // !WEBC_UTILS_QUERYSTRING_H
