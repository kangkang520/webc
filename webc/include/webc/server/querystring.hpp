#pragma once
#ifndef WEBC_UTILS_QUERYSTRING_H
#define WEBC_UTILS_QUERYSTRING_H

#include <iostream>
#include "../common/any.hpp"


namespace webc {
	namespace server {
		class querystring {
		public:
			//���캯��
			querystring(std::string str);
			querystring();
			void append(std::string str);
			bool parse();
			//��ȡһ��Ԫ��
			template <typename T>
			T& get(std::string key) {
				return m_map[key].cast<T>();
			}
		private:
			std::map<std::string, webc::any> m_map;
			std::string str = "";
			//���һ��key
			void add(std::string, std::string);
		};
	}
}

#endif // !WEBC_UTILS_QUERYSTRING_H
