#include "TypeTraits.h"

#include <cstdint> // for int8_t.

using namespace Std;

namespace {
// Confirm char types:
  static_assert(is_character<char>(), "char is a character");
  static_assert(is_character<const char>(), "const char is a character");
  static_assert(is_character<char&>(), "char ref is a character");
  static_assert(is_character<const char&>(), "const char ref is a character");

  static_assert(is_character<wchar_t>(), "wchar_t is a character");
  static_assert(is_character<const wchar_t>(), "const wchar_t is a character");
  static_assert(is_character<wchar_t&>(), "wchar_t ref is a character");
  static_assert(is_character<const wchar_t&>(),
      "const wchar_t ref is a character");

  static_assert(is_character<char16_t>(), "char16_t is a character");
  static_assert(is_character<const char16_t>(),
      "const char16_t is a character");
  static_assert(is_character<char16_t&>(), "char16_t ref is a character");
  static_assert(is_character<const char16_t&>(),
      "const char16_t ref is a character");

  static_assert(is_character<char32_t>(), "char32_t is a character");
  static_assert(is_character<const char32_t>(),
      "const char32_t is a character");
  static_assert(is_character<char32_t&>(), "char32_t ref is a character");
  static_assert(is_character<const char32_t&>(),
      "const char32_t ref is a character");

// Confirm non-char types:
  static_assert(!is_character<int8_t>(), "int8_t is not a character");
  static_assert(!is_character<uint8_t>(), "uint8_t is not a character");
  static_assert(!is_character<int>(), "int is not a character");
  
}
