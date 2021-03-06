#ifndef FORMAT_FORMATTER_H
#define FORMAT_FORMATTER_H

#include "Meta/Sequence.h"
#include "Meta/String.h"
#include "Meta/Struct.h"
#include "Meta/TypeTraits.h"

namespace Format {

using Meta::Sequence;
using Meta::String;

using Meta::Struct;
META_MAKE_INTEGER(index)

// Converts a sequence of characters into a Format type.
template <Character C, typename Index, typename Out, C... ins>
struct Parser;

template <Character C, C... ins>
using Formatter =
  typename Parser<C, Set_index<>, Sequence<String<C>>, ins...>::parsed;

template<Character C, C... chars>
constexpr auto operator""_Fmt()
{
  static_assert(Std::is_character<C>::value, "Formats must be characters");

  return Formatter<C, chars...>{};
}

template <size_t index>
struct Printer;

// Parser specialization declarations

// "?" => "?"
template <Character C, typename Index, C... outs, C in, C... ins, typename... Ts>
struct Parser<C, Index, Sequence<String<C, outs...>, Ts...>, in, ins...>;

// "{{" => "{"
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', '{', ins...>;

// "}}" => "}"
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '}', '}', ins...>;

// "{}" => Printer<Index> (special case)
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', '}', ins...>;

// "{?" => Printer<?> (temporary)
template <typename Index, char... outs, char... ins, char in, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', in, ins...>;

namespace details {

// "{{" => "{"
template <Character C, typename Index, typename Out, C... ins>
struct OpenEscaper;

// "}}" => "}"
template <Character C, typename Index, typename Out, C... ins>
struct CloseEscaper;

// "{}" => Printer<Index>
template <Character C, typename Index, typename Out, C... ins>
struct EmptyParameter;

// "{?" => Printer<?>
template <Character C, typename Index, typename Out, typename Parm, C... ins>
struct AddParameter;

} // details


// Parser specialization definitions.

// "?" => "?"
template <Character C, typename Index, C... outs, C in, C... ins, typename... Ts>
struct Parser<C, Index, Sequence<String<C, outs...>, Ts...>, in, ins...> {
  using parsed =
    typename Parser<C, Index,
             Sequence<String<C, outs..., in>, Ts...>,
             ins...>::parsed;
};

// "{{" => "{"
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', '{', ins...>
  : details::OpenEscaper<char, Index,
                         Sequence<String<char, outs...>, Ts...>,
                         ins...>
{};

// "}}" => "}"
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '}', '}', ins...>
  : details::CloseEscaper<char, Index,
                          Sequence<String<char, outs...>, Ts...>,
                          ins...>
{};

// "{}" => Printer<Index> (special case)
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', '}', ins...>
  : details::EmptyParameter<char, Index,
                            Sequence<String<char, outs...>, Ts...>,
                            ins...>
{};

// "{:}" => Printer<Index> (special case)
template <typename Index, char... outs, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', ':', '}', ins...>
  : details::EmptyParameter<char, Index,
                            Sequence<String<char, outs...>, Ts...>,
                            ins...>
{};


// "{:?" => Printer<?> (WIP)
template <typename Index, char... outs, char in, char... ins, typename... Ts>
struct Parser<char, Index,
              Sequence<String<char, outs...>, Ts...>,
              '{', ':', in, ins...>
  : details::AddParameter<char, Index,
                          Sequence<String<char, outs...>, Ts...>,
                          String<char, in>,
                          ins...>
{};



// No more characters: yield the Format sequence.
template <Character C, typename Index, typename... Ts>
struct Parser<C, Index, Sequence<Ts...>> {
  using parsed = typename Sequence<Ts...>::reverse;
};

namespace details {

template <Character C, typename Index, C... outs, C... ins, typename... Ts>
struct OpenEscaper<C, Index,
                   Sequence<String<C, outs...>, Ts...>,
                   ins...> {
  using parsed =
    typename Parser<C, Index,
                    Sequence<String<C, outs..., C{'{'}>, Ts...>,
                    ins...>::parsed;
};

template <Character C, typename Index, C... outs, C... ins, typename... Ts>
struct CloseEscaper<C, Index,
                    Sequence<String<C, outs...>, Ts...>,
                    ins...> {
  using parsed =
    typename Parser<C, Index,
                    Sequence<String<C, outs..., C{'}'}>, Ts...>,
                    ins...>::parsed;
};

// "{}" => Printer<Index> (temporary)
template <Character C, typename Index, C... outs, C... ins, typename... Ts>
struct EmptyParameter<C, Index,
                      Sequence<String<C, outs...>, Ts...>,
                      ins...> {
  using parsed = typename
    Parser<C, Add_index<Index, 1>,
           Sequence<String<C>, Printer<Index::index>, String<C, outs...>, Ts...>,
           ins...>::parsed;
};

// "{:..." => Printer<Index> (WIP)
template <Character C, typename Index, C... outs, C... ins, C... parms,
          typename... Ts>
struct AddParameter<C, Index,
                      Sequence<String<C, outs...>, Ts...>,
                      String<C, parms...>,
                      ins...> {
  using parsed = typename
    Parser<C, Add_index<Index, 1>,
           Sequence<String<C>, Printer<Index::index>, String<C, outs...>, Ts...>,
           ins...>::parsed;
};

// Trim leading empty string.
template <Character C, typename Index, C... ins, typename... Ts>
struct EmptyParameter<C, Index, Sequence<String<C>, Ts...>, ins...> {
  using parsed = typename
    Parser<C, Add_index<Index, 1>,
           Sequence<String<C>, Printer<Index::index>, Ts...>,
           ins...>::parsed;
};

// Trim trailing empty string.
template <Character C, typename Index, C... outs, typename... Ts>
struct EmptyParameter<C, Index, Sequence<String<C, outs...>, Ts...>> {
  using parsed = typename
    Parser<C, Add_index<Index, 1>,
           Sequence<Printer<Index::index>, String<C, outs...>, Ts...>>::parsed;
};

// Trim leading and trailing empty string.
template <Character C, typename Index, typename... Ts>
struct EmptyParameter<C, Index, Sequence<String<C>, Ts...>> {
  using parsed = typename
    Parser<C, Add_index<Index, 1>,
           Sequence<Printer<Index::index>, Ts...>>::parsed;
};

} // details

} // namespace Format

#endif // FORMAT_FORMATTER_H
