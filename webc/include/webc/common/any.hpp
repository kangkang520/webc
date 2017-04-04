#pragma once

#ifndef WEBC_COMMON_ANY_H
#define WEBC_COMMON_ANY_H

#include <iostream>
#include <string>
#include <memory>
#include <typeindex>

namespace webc {
	struct any
	{
		any(void) : m_tpIndex(std::type_index(typeid(void))) {}
		any(const any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}
		any(any && that) : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}

		//创建智能指针时，对于一般的类型，通过std::decay来移除引用和cv符，从而获取原始类型
		template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, any>::value, U>::type> any(U && value) : m_ptr(new Derived < typename std::decay<U>::type>(forward<U>(value))),
			m_tpIndex(type_index(typeid(typename std::decay<U>::type))) {}

		bool IsNull() const { return !bool(m_ptr); }

		template<class U> bool Is() const
		{
			return m_tpIndex == type_index(typeid(U));
		}

		//将any转换为实际的类型
		template<class U>
		U& cast()
		{
			if (!Is<U>())
			{
				std::cerr << "can not cast " << typeid(U).name() << " to " << m_tpIndex.name() << endl;
				throw bad_cast();
			}

			auto derived = dynamic_cast<Derived<U>*> (m_ptr.get());
			return derived->m_value;
		}

		any& operator=(const any& a)
		{
			if (m_ptr == a.m_ptr)
				return *this;

			m_ptr = a.Clone();
			m_tpIndex = a.m_tpIndex;
			return *this;
		}

	private:
		struct Base;
		typedef std::unique_ptr<Base> BasePtr;

		struct Base
		{
			virtual ~Base() {}
			virtual BasePtr Clone() const = 0;
		};

		template<typename T>
		struct Derived : Base
		{
			template<typename U>
			Derived(U && value) : m_value(forward<U>(value)) { }

			BasePtr Clone() const
			{
				return BasePtr(new Derived<T>(m_value));
			}

			T m_value;
		};

		BasePtr Clone() const
		{
			if (m_ptr != nullptr)
				return m_ptr->Clone();

			return nullptr;
		}

		BasePtr m_ptr;
		std::type_index m_tpIndex;
	};
}

#endif