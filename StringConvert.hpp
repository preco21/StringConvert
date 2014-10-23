/**
*	StringConvert.hpp
*
*/

#ifndef STRING_CONVERT_HPP
#define STRING_CONVERT_HPP

#include <string>
#include <locale>
#include <codecvt>

class StringConvert final
{
public :

	// Delete destructor
	~StringConvert() = delete;

	// WBCS to MBCS
	static std::string wideStringToAnsiString(const std::wstring& wstring, const std::locale& locale = std::locale{""});

	// MBCS to WBCS
	static std::wstring ansiStringToWideString(const std::string& string, const std::locale& locale = std::locale{""});

	// UTF-8 -> UTF-16
	static std::u16string u8StringToU16String(const std::string& u8String);

	// UTF-8 -> UTF-32
	static std::u32string u8StringToU32String(const std::string& u8String);

	// UTF-16 -> UTF-8
	static std::string u16StringToU8String(const std::u16string& u16String);

	// UTF-16 -> UTF-32
	static std::u32string u16StringToU32String(const std::u16string& u16String);

	// UTF-32 -> UTF-8
	static std::string u32StringToU8String(const std::u32string& u32String);

	// UTF-32 -> UTF-16
	static std::u16string u32StringToU16String(const std::u32string& u32String);

private :

	// Member data
	static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> s_u32Converter;
	static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> s_u16Converter;
};

#endif // STRING_CONVERT_HPP