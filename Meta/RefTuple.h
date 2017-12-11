#ifndef REF_TUPLE_H
#define REF_TUPLE_H

#include "TypeTraits.h"

#include <cstddef> // for size_t.

namespace Meta {

struct TagBase {};

template <typename T>
concept bool Tag = std::is_base_of_v<TagBase, T>;

template <char... chars>
struct TagString : TagBase {
  template <typename T>
  constexpr auto operator=(const T& item) const;
};

inline namespace literals {

template<Character C, C... chars>
constexpr auto operator""_a()
{
  return TagString<chars...>{};
}

} // namespace literals


template <Tag, typename T>
struct Tagged
{
  const T& item;
};

template <char... chars>
template <typename T>
constexpr auto TagString<chars...>::operator=(const T& item) const
{
  return Tagged<TagString<chars...>, T>{item};
}


// A tuple of references, with a special exception for C-style strings,
// which are converted to string_views.

template <typename... Types>
class RefTuple;

template <typename First, typename... Rest>
class RefTuple<First, Rest...>
  : private RefTuple<Rest...>
{
  public:
    constexpr RefTuple(const First& first, const Rest&... rest)
      : RefTuple<Rest...>{rest...}
      , item(first)
    {}

    const First& item;

    template <size_t N>
    constexpr const auto& get() const;

    constexpr const auto&
    rest() const {
      return static_cast<const RefTuple<Rest...>&>(*this);
    }
};

template <>
class RefTuple<> {
  public:
    constexpr RefTuple()
    {}

  template <size_t N>
  constexpr void get() const
  {
    static_assert(N != N, "Cannot get<> from empty RefTuple");
  }
};

namespace details {

  template <size_t N, typename... Ts>
  struct RefTupleGetter;

  template <size_t N, typename First, typename... Rest>
  struct RefTupleGetHelper
  {
    static constexpr const auto& get(const RefTuple<First, Rest...>& tuple) {
      return RefTupleGetHelper<N-1, Rest...>::get(tuple.rest());
    }
  };

  template <typename First, typename... Rest>
  struct RefTupleGetHelper<0, First, Rest...>
  {
    static constexpr const First& get(const RefTuple<First, Rest...>& tuple) {
      return tuple.item;
    }
  };

  template <size_t N, typename... Ts>
  struct RefTupleGetter : public RefTupleGetHelper<N, Ts...> {
    static_assert(N < sizeof...(Ts), "get subscript out of bounds");
  };

} // namespace details

template <typename First, typename... Rest>
template <size_t N>
constexpr const auto& RefTuple<First, Rest...>::get() const {
  return details::RefTupleGetter<N, First, Rest...>::get(*this);
}

} // Meta

#endif // REF_TUPLE_H
