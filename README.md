# DynamicString
Dynamic string class with no external libs use

## Usage
Project includes an example of use alongside `std::string` in `main.cpp`.

- Run from command line with arguments to use them as strings
- Or run without arguments to use strings from `strings.txt`
- Program outputs entered strings in reverse lexicographic order
- Only English strings are supported
- Contains alternatives to `std::strlen`, `std::memcpy`, `std::swap`, `std::sort` (my sort is not optimised)

## Possible improvements
- Use buffer (static `char` array) of small size (e.g. 16)
- Use pre-allocation, store capacity
- Scrap this and use `std::string` or `std::wstring` or ICU
