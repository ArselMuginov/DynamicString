#include "String.hpp"
#include <exception>

// If usage of std::strlen, std::memcpy, std::swap is not permitted,
// there are alternative functions to use (e.g. std::strlen -> ::strlen)

namespace
{
	std::size_t strlen(const char* const str)
	{
		const char* ptr = str;
		for (; *ptr != '\0'; ++ptr);
		return ptr - str;
	}

	void memcpy(void* dst, const void* src, std::size_t size)
	{
		char* d = (char*) dst;
		const char* s = (const char*) src;

		while (size--)
		{
			*d++ = *s++;
		}
	}

	template<typename T> void swap(T& t1, T& t2) {
		T temp(std::move(t1));
		t1 = std::move(t2);
		t2 = std::move(temp);
	}
}

namespace ds
{
	String::String() :
		m_length(0),
		m_data(nullptr)
	{
	}

	// TODO: not belongs
	String::String(const std::size_t length) :
		m_length(length + 1),
		m_data(new char[m_length])
	{
		m_data[0] = '\0';
		--m_length;
	}

	String::String(const char* const string) :
		m_length(std::strlen(string) + 1),
		m_data(new char[m_length])
	{
		std::memcpy(m_data, string, m_length);
		--m_length;
	}

	String::String(const char* const string, const std::size_t length) :
		m_length(length + 1),
		m_data(new char[m_length])
	{
		std::memcpy(m_data, string, m_length);
		--m_length;
	}

	String::String(const std::string& string) :
		m_length(string.length() + 1),
		m_data(new char[m_length])
	{
		std::memcpy(m_data, string.c_str(), m_length);
		--m_length;
	}

	String::String(const String& that) :
		m_length(that.m_length + 1),
		m_data(new char[m_length])
	{
		std::memcpy(m_data, that.m_data, m_length);
		--m_length;
	}

	String::String(String&& that) noexcept :
		String()
	{
		swap(*this, that);
	}

	String::~String()
	{
		delete[] m_data;
	}

	std::size_t String::length() const
	{
		return m_length;
	}

	std::size_t String::max_length() const
	{
		
		return static_cast<std::size_t>(-1);
	}

	int compare(const char* first, const char* second, std::size_t length)
	{
		for (; 0 < length; --length, ++first, ++second) {
			if (*first != *second) {
				return *first < *second ? -1 : +1;
			}
		}

		return 0;
	}

	int compare(const String& left, const String& right)
	{
		const int lLength = left.m_length;
		const int rLength = right.m_length;
		const int comp = compare(left.m_data, right.m_data, lLength < rLength ? lLength : rLength);
		
		if (comp != 0)
		{
			return comp;
		}

		if (lLength < rLength)
		{
			return -1;
		}

		if (lLength > rLength)
		{
			return 1;
		}

		return 0;
	}

	void swap(String& first, String& second) noexcept
	{
		using std::swap;

		swap(first.m_data, second.m_data);
		swap(first.m_length, second.m_length);
	}

	String operator+(const String& left, const String& right)
	{
		if (left.max_length() - left.m_length < right.m_length)
		{
			throw std::length_error("String too long");
		}

		String sum = String(left.m_length + right.m_length);
		std::memcpy(&sum, &left, left.m_length);
		std::memcpy(&sum + left.m_length, &right, right.m_length);
		sum[sum.m_length] = '\0';
		return sum;
	}

	bool operator==(const String& left, const String& right)
	{
		return left.m_length == right.m_length && compare(left, right) == 0;
	}

	bool operator!=(const String& left, const String& right)
	{
		return !(left == right);
	}

	bool operator<(const String& left, const String& right)
	{
		return compare(left, right) < 0;
	}

	bool operator<=(const String& left, const String& right)
	{
		return !(right < left);
	}

	bool operator>(const String& left, const String& right)
	{
		return right < left;
	}

	bool operator>=(const String& left, const String& right)
	{
		return !(left < right);
	}

	std::ostream& operator<<(std::ostream& os, String const& that)
	{
		for (std::size_t i = 0; i < that.m_length; ++i)
		{
			os << that.m_data[i];
		}

		return os;
	}

	String& String::operator=(String that)
	{
		swap(*this, that);
		return *this;
	}

	char& String::operator[](const std::size_t offset)
	{
		if (offset > m_length)
		{
			throw std::out_of_range("String subscript out of range");
		}

		return m_data[offset];
	}

	const char& String::operator[](const std::size_t offset) const
	{
		if (offset > m_length)
		{
			throw std::out_of_range("String subscript out of range");
		}

		return m_data[offset];
	}

	String String::operator+=(const String& that)
	{
		if (max_length() - m_length < that.m_length)
		{
			throw std::length_error("String too long");
		}

		m_length += that.m_length;
		char* new_data = new char[m_length];

		using std::swap;
		swap(m_data, new_data);
		delete[] new_data;
		
		return *this;
	}
}
