#ifndef FORMAT_FORMATTER_H
#define FORMAT_FORMATTER_H

#include "Meta/Sequence.h"
#include "Meta/String.h"
#include "Meta/TypeTraits.h"

namespace Format {

using Meta::Sequence;
using Meta::String;

template <typename C, typename Out, C... ins>
struct Parser;

template <typename C, C... ins>
using Formatter = typename Parser<C, Sequence<String<C>>, ins...>::parsed;

template <typename C, C... outs, C in, C... ins, typename... Ts>
struct Parser<C, Sequence<String<C, outs...>, Ts...>, in, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C, outs..., in>, Ts...>, ins...>::parsed;
};

// "{{" => "{"
template <typename C, typename Out, C... ins>
struct OpenParser;

template <typename C, C... outs, C... ins, typename... Ts>
struct OpenParser<C, Sequence<String<C, outs...>, Ts...>, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C, outs..., C{'{'}>, Ts...>, ins...>::parsed;
};

template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '{', '{', ins...>
  : OpenParser<char, Sequence<String<char, outs...>, Ts...>, ins...>
{};

template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'{', L'{', ins...>
  : OpenParser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, ins...>
{};


// "}}" => "}"
template <typename C, typename Out, C... ins>
struct CloseParser;

template <typename C, C... outs, C... ins, typename... Ts>
struct CloseParser<C, Sequence<String<C, outs...>, Ts...>, ins...> {
  using parsed =
    typename Parser<C, Sequence<String<C, outs..., C{'}'}>, Ts...>, ins...>::parsed;
};

template <char... outs, char... ins, typename... Ts>
struct Parser<char, Sequence<String<char, outs...>, Ts...>, '}', '}', ins...>
  : CloseParser<char, Sequence<String<char, outs...>, Ts...>, ins...>
{};

template <wchar_t... outs, wchar_t... ins, typename... Ts>
struct Parser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, L'}', L'}', ins...>
  : CloseParser<wchar_t, Sequence<String<wchar_t, outs...>, Ts...>, ins...>
{};


template <typename C, C... outs, typename... Ts>
struct Parser<C, Sequence<String<C, outs...>, Ts...>> {
  using parsed = Sequence<String<C, outs...>, Ts...>;
};

template<typename C, C... chars>
constexpr auto operator""_Fmt()
{
  static_assert(Std::is_character<C>::value, "Formats must be characters");

  return Formatter<C, chars...>{};
}

} // namespace Format

#endif // FORMAT_FORMATTER_H
