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
