#ifndef TAG_H
#define TAG_H

#include "TypeTraits.h"

// Concepts:
//   A Tag is a distinguishable type intended to be associated with a variable.
//   Tagged variables (types) have a Tag.
//   Untagged variables (types) do not have a Tag.

// Templates:
//   TagStrings are compiletime strings with a UDL `_a` that can Tag a variable
//   (reference) by the assignment operator, e.g. `"mytag"_a=42`.


namespace Meta {

template <typename T>
concept bool Tag = false;

template <typename T>
concept bool Tagged = false;

template <typename T>
concept bool Untagged = false;

template <Character C, C... chars>
struct TagString;

inline namespace literals {

template<Character C, C... chars>
constexpr auto operator""_a();

} // namespace literals

inline namespace details {

  struct TagBase {};
  struct TaggedBase {};

}

template <typename T>
concept bool Tag = std::is_base_of_v<TagBase, T>;

template <Character C, C... chars>
struct TagString : TagBase {
  template <typename T>
  constexpr auto operator=(const T& item) const;

  template <typename U>
  static constexpr bool is() {
    return std::is_same<U, TagString<C, chars...>>::value;
  }
};

inline namespace literals {

template<Character C, C... chars>
constexpr auto operator""_a()
{
  return TagString<C, chars...>{};
}

} // namespace literals


template <typename T>
concept bool Tagged = std::is_base_of_v<TaggedBase, T>;

template <typename T>
concept bool Untagged = !std::is_base_of_v<TaggedBase, T>;

template <Tag TT, typename T>
struct TaggedItem : TaggedBase
{
  constexpr TaggedItem(const T& it)
    : TaggedBase{}
    , item{it}
  {}

  const T& item;

  using Tag = TT;
};

template<Character C1, Character C2, C1... chars_1, C2... chars_2>
constexpr bool operator==(
    const TagString<C1, chars_1...>& s1, const TagString<C2, chars_2...>& s2)
{
  return false; // unless C1 == C2 and chars match, below.
}

template <Character C, C... chars>
template <typename T>
constexpr auto TagString<C, chars...>::operator=(const T& item) const
{
  return TaggedItem<TagString<C, chars...>, T>{item};
}

template<Character C, C... chars_1, C... chars_2>
constexpr bool operator==(
    const TagString<C, chars_1...>& s1, const TagString<C, chars_2...>& s2)
{
  using S2 = TagString<C, chars_2...>;

  return s1.template is<S2>();
}

template<Character C1, Character C2, C1... chars_1, C2... chars_2>
constexpr bool operator!=(
    const TagString<C1, chars_1...>& s1, const TagString<C2, chars_2...>& s2)
{
  return !(s1 == s2);
}

} // Meta

#endif // TAG_H
