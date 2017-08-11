/**
*  StringConvert.cpp
*
*/

#include "StringConvert.hpp"
#include <vector>

using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;

#if defined(_MSVC_CONVERT_WORKAROUND)
  std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> StringConvert::s_u32Converter;
  std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> StringConvert::s_u16Converter;
#else
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> StringConvert::s_u32Converter;
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> StringConvert::s_u16Converter;
#endif

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
#if defined(_MSVC_CONVERT_WORKAROUND)
  auto&& workaround = s_u16Converter.from_bytes(u8String);
  return std::u16string(reinterpret_cast<const char16_t*>(workaround.c_str()));
#else
  return s_u16Converter.from_bytes(u8String);
#endif
}

std::u32string StringConvert::u8StringToU32String(const std::string& u8String)
{
#if defined(_MSVC_CONVERT_WORKAROUND)
  auto&& workaround = s_u32Converter.from_bytes(u8String);
  return std::u32string(reinterpret_cast<const char32_t*>(workaround.c_str()));
#else
  return s_u32Converter.from_bytes(u8String);
#endif
}

std::string StringConvert::u16StringToU8String(const std::u16string& u16String)
{
#if defined(_MSVC_CONVERT_WORKAROUND)
  using workaround_str = std::basic_string<int16_t, std::char_traits<int16_t>, std::allocator<int16_t> >;
  workaround_str workaround(reinterpret_cast<const int16_t*>(u16String.c_str()));
  return s_u16Converter.to_bytes(workaround);
#else
  return s_u16Converter.to_bytes(u16String);
#endif
}

std::u32string StringConvert::u16StringToU32String(const std::u16string& u16String)
{
  std::string temp{u16StringToU8String(u16String)};

  return u8StringToU32String(temp);
}

std::string StringConvert::u32StringToU8String(const std::u32string& u32String)
{
#if defined(_MSVC_CONVERT_WORKAROUND)
  using workaround_str = std::basic_string<int32_t, std::char_traits<int32_t>, std::allocator<int32_t> >;
  workaround_str workaround(reinterpret_cast<const int32_t*>(u32String.c_str()));
  return s_u32Converter.to_bytes(workaround);
#else
  return s_u32Converter.to_bytes(u32String);
#endif
}

std::u16string StringConvert::u32StringToU16String(const std::u32string& u32String)
{
  std::string temp{u32StringToU8String(u32String)};

  return u8StringToU16String(temp);
}
