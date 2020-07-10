#pragma once
#include <ostream> // std::ostream

namespace ds
{
	class String
	{
	public:
		String();

		// Constructs String from null-terminated string
		String(const char* const string);

		// Constructs String from characters with given length.
		// Last '\0' not counted in given length.
		String(const char* const string, const std::size_t length);
		
		String(const std::string& string);
		String(const String& that);
		String(String&& that) noexcept;
		~String();

		std::size_t length() const;
		std::size_t max_length() const;

		// Lexicographically compares two char arrays with same length.
		// Case sensitive.
		friend int compare(const char* first, const char* second, std::size_t length);

		// Lexicographically compares two strings.
		// Case sensitive.
		friend int compare(const String& left, const String& right);

		friend void swap(String& first, String& second) noexcept;

		String& operator=(String that);

		char& operator[](const std::size_t offset);
		const char& operator[](const std::size_t offset) const;

		friend String operator+(const String& left, const String& right);
		String operator+=(const String& that);

		friend bool operator==(const String& left, const String& right);
		friend bool operator!=(const String& left, const String& right);
		friend bool operator<(const String& left, const String& right);
		friend bool operator<=(const String& left, const String& right);
		friend bool operator>(const String& left, const String& right);
		friend bool operator>=(const String& left, const String& right);

		friend std::ostream& operator<<(std::ostream& os, String const& that);

	private:
		String(const std::size_t length);

		std::size_t m_length;
		char* m_data;
	};
}
