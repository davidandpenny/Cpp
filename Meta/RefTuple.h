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

template <typename... Types>
class RefTupleBase;

template <typename First, typename... Rest>
class RefTupleBase<First, Rest...>
  : public RefTuple<Rest...>
{
  public:
    constexpr RefTupleBase(const First& first, const Rest&... rest)
      : RefTuple<Rest...>{rest...}
      , item{first}
    {}
    
    const First& item;

    template <size_t N>
    constexpr const auto& get() const;

    constexpr const auto&
    rest() const {
      return static_cast<const RefTuple<Rest...>&>(*this);
    }
};



template <typename First, typename... Rest>
class RefTuple<First, Rest...>
  : public RefTupleBase<First, Rest...>
{
  public:
    constexpr RefTuple(const First& first, const Rest&... rest)
      : RefTupleBase<First, Rest...>{first, rest...}
    {}

    using tag = void;
};

template <Tag FirstTag, typename First, typename... Rest>
class RefTuple<Tagged<FirstTag, First>, Rest...>
  : public RefTuple<Rest...>
{
  public:

    using TF = Tagged<FirstTag, First>;

    constexpr RefTuple(const TF& first, const Rest&... rest)
      : RefTupleBase<First, Rest...>{rest...}
    {}

    using tag = FirstTag;
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
    static constexpr const auto& get(
        const RefTupleBase<First, Rest...>& tuple) {
      return RefTupleGetHelper<N-1, Rest...>::get(tuple.rest());
    }
  };

  template <typename First, typename... Rest>
  struct RefTupleGetHelper<0, First, Rest...>
  {
    static constexpr const First& get(
        const RefTupleBase<First, Rest...>& tuple) {
      return tuple.item;
    }
  };

  template <size_t N, typename... Ts>
  struct RefTupleGetter : public RefTupleGetHelper<N, Ts...> {
    static_assert(N < sizeof...(Ts), "get subscript out of bounds");
  };

  template <Tag Target, typename... Ts>
  struct RefTupleFinder;

  template <Tag Target, typename First, typename... Rest>
  struct RefTupleFinder<Target, First, Rest...>
  {
    static constexpr const auto& get(const RefTuple<First, Rest...>& tuple) {
      return RefTupleFinder<Target, Rest...>::get(tuple.rest());
    }
  };

  template <Tag Target, typename First, typename... Rest>
  struct RefTupleFinder<Target, Tagged<Target, First>, Rest...>
  {
    static constexpr const First& find(const RefTuple<First, Rest...>& tuple) {
      return tuple.item;
    }
  };

  template <Tag Target>
  struct RefTupleFinder<Target>
  {
    static_assert(sizeof(Target) == 0, "Target not Found in RefTuple");
  };

} // namespace details

template <typename First, typename... Rest>
template <size_t N>
constexpr const auto& RefTupleBase<First, Rest...>::get() const {
  return details::RefTupleGetter<N, First, Rest...>::get(*this);
}

} // Meta

#endif // REF_TUPLE_H
