#ifndef META_STRING_H
#define META_STRING_H

#include "TypeTraits.h"

#include <cstddef> // for size_t.

namespace Meta {

// A compiletime string, conveniently constructable by "hello world"_S.
// (use decltype"x"_S) to get the String type.
// Needs push_back, pop_front, etc.
template <Character C, C... chars>
struct String
{
  using type = String<C, chars...>;

  template <typename U>
  static constexpr bool is() {
    return std::is_same<U, String<C, chars...>>::value;
  }
};

inline namespace literals {

template<Character C, C... chars>
constexpr auto operator""_S()
{
  return String<C, chars...>{};
}

} // namespace literals

template<Character C1, C1... chars_1, Character C2, C2... chars_2>
constexpr bool
  operator==(const String<C1, chars_1...>& s1, const String<C2, chars_2...>& s2)
{
  static_assert(C1{} != C1{}, "Mismatched Character types in String compare");

  return false;
}

template<Character C, C... chars_1, C... chars_2>
constexpr bool
  operator==(const String<C, chars_1...>& s1, const String<C, chars_2...>& s2)
{
  using S2 = String<C, chars_2...>;

  return s1.template is<S2>();
}

template<Character C, C... chars_1, C... chars_2>
constexpr bool
  operator!=(const String<C, chars_1...>& s1, const String<C, chars_2...>& s2)
{
  return !(s1 == s2);
}

template<Character C, C... chars_1, C... chars_2>
constexpr auto
  operator+(const String<C, chars_1...>& s1, const String<C, chars_2...>& s2)
{
  return String<C, chars_1..., chars_2...>{};
}

} // Meta

#endif // META_STRING_H
