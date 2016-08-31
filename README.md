# StringConvert

> A simple C++11 based helper for converting string between a various charset

**C++11 implemented compiler required**

## Methods

```c++
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
```

## Usage

```c++
#include "StringConvert.hpp"
#include <iostream>

int main()
{
  std::cout << StringConvert::wideStringToAnsiString(L"히이이익!") << std::endl;
  return 0;
}
```

## Trouble Shooting

Some cases you should set locales, see details:

* http://en.cppreference.com/w/cpp/locale/setlocale
* http://en.cppreference.com/w/cpp/locale/locale/global

## License

CC0 (Public Domain)
