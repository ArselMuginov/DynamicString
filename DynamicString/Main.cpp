#include "DynamicString/String.hpp"
#include <iostream>
#include <vector>
#include <algorithm> // std:sort
#include <fstream> // std::ifstream
#include <string> // std::getline

// Works only with English strings
// Gets strings from command line arguments
// With no arguments gets strings from strings.txt
// To use terrible sort from this file, swap comments in lexSortCI()

// Possible improvements:
// - Use buffer (static char array) of small size (e.g. 16)
// - Use pre-allocation, store capacity
// - Scrap this and use std::string or std::wstring or ICU

namespace
{
	template<typename Arg>
	using Pred = bool (*)(const Arg& left, const Arg& right);

	// Sort vector according to given predicate
	template<typename Str>
	void sort(std::vector<Str>& strings, Pred<Str> pred)
	{
		std::size_t size = strings.size();
		for (std::size_t i = 0; i < size; ++i)
		{
			for (std::size_t j = 0; j < size - i - 1; ++j)
			{
				if (!pred(strings[j], strings[j + 1]))
				{
					Str temp(std::move(strings[j]));
					strings[j] = std::move(strings[j + 1]);
					strings[j + 1] = std::move(temp);
				}
			}
		}
	}
}

// Transform string to lower case
template<typename Str>
Str toLower(Str string)
{
	for (std::size_t i = 0; i < string.length(); ++i)
	{
		string[i] |= 32;
	}

	return string;
}

// Compare strings in reverse order, case insensitive
template<typename Str>
bool compareReverseCI(const Str& left, const Str& right)
{
	return toLower(left) > toLower(right);
}

// Sort in reverse lexicographic order, case insensitive
template<typename Str>
void sortReverseLexCI(std::vector<Str>& strings)
{
	std::sort(strings.begin(), strings.end(), compareReverseCI<Str>);
	//::sort(strings, compareReverseCI<Str>);
}

int main(int argc, char* argv[])
{
	const std::string filename("strings.txt");
	std::vector<ds::String> dsStrings;
	std::vector<std::string> stdStrings;

	if (argc == 1)
	{
		std::ifstream stream(filename);
		std::string str;
		while (std::getline(stream, str))
		{
			dsStrings.push_back(str);
			stdStrings.push_back(str);
		}
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			dsStrings.push_back(argv[i]);
			stdStrings.push_back(argv[i]);
		}
	}

	sortReverseLexCI(dsStrings);
	sortReverseLexCI(stdStrings);

	std::cout << "Sorted ds::String vector:" << std::endl;
	for (auto& string : dsStrings)
	{
		std::cout << string << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Sorted std::string vector:" << std::endl;
	for (auto& string : stdStrings)
	{
		std::cout << string << std::endl;
	}

	return 0;
}
