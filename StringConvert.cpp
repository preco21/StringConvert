/**
*  StringConvert.cpp
*
*/

#include "StringConvert.hpp"
#include <vector>

using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;

std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> StringConvert::s_u32Converter;
std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> StringConvert::s_u16Converter;

std::string StringConvert::wideStringToAnsiString(const std::wstring& wstring, const std::locale& locale)
{
  const codecvt_t& codecvt(std::use_facet<codecvt_t>(locale));
  std::mbstate_t state;
  std::vector<char> buffer((wstring.size() + 1) * codecvt.max_length());
  const wchar_t* inNext{wstring.c_str()};
  char* outNext{&buffer[0]};

  std::codecvt_base::result result{codecvt.out(state, wstring.c_str(), wstring.c_str() + wstring.size(), inNext, &buffer[0], &buffer[0] + buffer.size(), outNext)};

  if (result == std::codecvt_base::error)
    throw std::runtime_error("can not convert wstring to string");

  return &buffer[0];
}

std::wstring StringConvert::ansiStringToWideString(const std::string& string, const std::locale& locale)
{
  const codecvt_t& codecvt(std::use_facet<codecvt_t>(locale));
  std::mbstate_t state{};
  std::vector<wchar_t> buffer(string.size() + 1);
  const char* inNext{string.c_str()};
  wchar_t* outNext{&buffer[0]};

  std::codecvt_base::result result{codecvt.in(state, string.c_str(), string.c_str() + string.size(), inNext, &buffer[0], &buffer[0] + buffer.size(), outNext)};

  if (result == std::codecvt_base::error)
    throw std::runtime_error("can not convert string to wstring");

  return &buffer[0];
}

std::u16string StringConvert::u8StringToU16String(const std::string& u8String)
{
  return s_u16Converter.from_bytes(u8String);
}

std::u32string StringConvert::u8StringToU32String(const std::string& u8String)
{
  return s_u32Converter.from_bytes(u8String);
}

std::string StringConvert::u16StringToU8String(const std::u16string& u16String)
{
  return s_u16Converter.to_bytes(u16String);
}

std::u32string StringConvert::u16StringToU32String(const std::u16string& u16String)
{
  std::string temp{u16StringToU8String(u16String)};

  return u8StringToU32String(temp);
}

std::string StringConvert::u32StringToU8String(const std::u32string& u32String)
{
  return s_u32Converter.to_bytes(u32String);
}

std::u16string StringConvert::u32StringToU16String(const std::u32string& u32String)
{
  std::string temp{u32StringToU8String(u32String)};

  return u8StringToU16String(temp);
}
