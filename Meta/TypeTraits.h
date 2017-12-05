#ifndef META_TYPE_TRAITS_H
#define META_TYPE_TRAITS_H

#include <type_traits>

// Extensions to std.
namespace Std {

template <typename T>
struct is_character : std::false_type {};

template <>
struct is_character<char> : std::true_type {};
template <>
struct is_character<const char> : std::true_type {};
template <>
struct is_character<char&> : std::true_type {};
template <>
struct is_character<const char&> : std::true_type {};

template <>
struct is_character<char16_t> : std::true_type {};
template <>
struct is_character<const char16_t> : std::true_type {};
template <>
struct is_character<char16_t&> : std::true_type {};
template <>
struct is_character<const char16_t&> : std::true_type {};

template <>
struct is_character<char32_t> : std::true_type {};
template <>
struct is_character<const char32_t> : std::true_type {};
template <>
struct is_character<char32_t&> : std::true_type {};
template <>
struct is_character<const char32_t&> : std::true_type {};

template <>
struct is_character<wchar_t> : std::true_type {};
template <>
struct is_character<const wchar_t> : std::true_type {};
template <>
struct is_character<wchar_t&> : std::true_type {};
template <>
struct is_character<const wchar_t&> : std::true_type {};

} // Std

template <typename T>
concept bool Character = Std::is_character<T>::value;

#endif // META_TYPE_TRAITS_H
