#ifndef FORMAT_FORMATTER_H
#define FORMAT_FORMATTER_H

#include "Meta/Sequence.h"
#include "Meta/String.h"
#include "Meta/TypeTraits.h"

namespace Format {

using Meta::Sequence;
using Meta::String;

// Converts a sequence of characters into a Format type.
template <typename C, typename Out, C... ins>
struct Parser;

template <typename C, C... ins>
using Formatter = typename Parser<C, Sequence<String<C>>, ins...>::parsed;

template<typename C, C... chars>
constexpr auto operator""_Fmt()
{
  static_assert(Std::is_character<C>::value, "Formats must be characters");

  return Formatter<C, chars...>{};
}

// Parser specialization declarations

// "?" => "?"
template <typename C, C... outs, C in, C... ins, typename... Ts>
struct Parser<C, Sequence<String<C, outs...>, Ts...>, in, ins...>;

// "{{" => "{"
template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '{', '{', ins...>;
template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'{', L'{',
  ins...>;

// "}}" => "}"
template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '}', '}', ins...>;
template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'}', L'}',
              ins...>;

// "{}" => "%" (temporary)
template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '{', '}', ins...>;
template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'{', L'}',
  ins...>;

namespace details {

// "{{" => "{"
template <typename C, typename Out, C... ins>
struct OpenEscaper;

// "}}" => "}"
template <typename C, typename Out, C... ins>
struct CloseEscaper;

// "{}" => "%"
template <typename C, typename Out, C... ins>
struct OpenParameter;

} // details


// Parser specialization definitions.

// "?" => "?"
template <typename C, C... outs, C in, C... ins, typename... Ts>
struct Parser<C, Sequence<String<C, outs...>, Ts...>, in, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C, outs..., in>, Ts...>, ins...>::parsed;
};

// "{{" => "{"
template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '{', '{', ins...>
  : details::OpenEscaper<char, Sequence<String<char, outs...>, Ts...>, ins...>
{};
template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'{', L'{',
              ins...>
  : details::OpenEscaper<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>,
                         ins...>
{};

// "}}" => "}"
template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '}', '}', ins...>
  : details::CloseEscaper<char, Sequence<String<char, outs...>, Ts...>, ins...>
{};
template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'}', L'}',
              ins...>
  : details::CloseEscaper<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>,
                          ins...>
{};

// "{}" => "%" (temporary)
template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '{', '}', ins...>
  : details::OpenParameter<char, Sequence<String<char, outs...>, Ts...>, ins...>
{};
template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'{', L'}',
  ins...>
  : details::OpenParameter<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>,
                         ins...>
{};

// No more characters: yield the Format sequence.
template <typename C, C... outs, typename... Ts>
struct Parser<C, Sequence<String<C, outs...>, Ts...>> {
  using parsed = Sequence<String<C, outs...>, Ts...>;
};

namespace details {

template <typename C, C... outs, C... ins, typename... Ts>
struct OpenEscaper<C, Sequence<String<C, outs...>, Ts...>, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C, outs..., C{'{'}>, Ts...>, ins...>::parsed;
};

template <typename C, C... outs, C... ins, typename... Ts>
struct CloseEscaper<C, Sequence<String<C, outs...>, Ts...>, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C, outs..., C{'}'}>, Ts...>, ins...>::parsed;
};

template <typename C, C... outs, C... ins, typename... Ts>
struct OpenParameter<C, Sequence<String<C, outs...>, Ts...>, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C>, String<C, C{'*'}>, String<C, outs...>, Ts...>, ins...>::parsed;
};

} // details

} // namespace Format

#endif // FORMAT_FORMATTER_H
