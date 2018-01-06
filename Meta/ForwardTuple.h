#ifndef FORWARD_TUPLE_H
#define FORWARD_TUPLE_H

#include "Tag.h"
#include "TypeTraits.h"

#include <cstddef> // for size_t.

namespace Meta {

// A tuple of references, with a special exception for TODO C-style strings,
// which are converted to string_views.

template <typename... Types>
struct ForwardTuple
{
  static_assert(sizeof...(Types) == 0, "all or no parameters must be tagged");

  constexpr ForwardTuple(const Types&...) {}
};

template <typename... Types>
class ForwardTupleBase;

template <typename First, typename... Rest>
struct ForwardTupleBase<First, Rest...>
  : public ForwardTuple<Rest...>
{
  constexpr ForwardTupleBase(const First& first, const Rest&... rest)
    : ForwardTuple<Rest...>{rest...}
    , item{first}
  {}
  
  const First& item;

  template <size_t N>
  constexpr const auto& get() const;

  constexpr const auto&
  rest() const {
    return static_cast<const ForwardTuple<Rest...>&>(*this);
  }
};

template <Untagged First, Untagged... Rest>
struct ForwardTuple<First, Rest...>
  : ForwardTupleBase<First, Rest...>
{
  constexpr ForwardTuple(const First& first, const Rest&... rest)
    : ForwardTupleBase<First, Rest...>{first, rest...}
  {}

  using tag = void;
};

template <typename FirstTag, typename First, Tagged... Rest>
struct ForwardTuple<TaggedItem<FirstTag, First>, Rest...>
  : ForwardTupleBase<TaggedItem<FirstTag, First>, Rest...>
{
  using TaggedFirst = TaggedItem<FirstTag, First>;

  constexpr ForwardTuple(const TaggedFirst& first, const Rest&... rest)
    : ForwardTupleBase<TaggedFirst, Rest...>{first, rest...}
    , item{first.item}
  {}

  const First& item;

  template <Tag T>
  constexpr const auto& find(T) const;
  
  using tag = FirstTag;
};

template <>
struct ForwardTuple<> {
  constexpr ForwardTuple()
  {}

  template <size_t N>
  constexpr void get() const
  {
    static_assert(N != N, "Cannot get<> from empty ForwardTuple");
  }

  template <Tag T>
  constexpr void find(T) const
  {
    static_assert(T{} != T{}, "Cannot find<> in empty ForwardTuple");
  }
};

namespace details {

  template <size_t N, typename... Ts>
  struct ForwardTupleGetter;

  template <size_t N, typename First, typename... Rest>
  struct ForwardTupleGetHelper
  {
    static constexpr const auto& get(
        const ForwardTupleBase<First, Rest...>& tuple) {
      return ForwardTupleGetHelper<N-1, Rest...>::get(tuple.rest());
    }
  };

  template <typename First, typename... Rest>
  struct ForwardTupleGetHelper<0, First, Rest...>
  {
    static constexpr const First& get(
        const ForwardTupleBase<First, Rest...>& tuple) {
      return tuple.item;
    }
  };

  template <size_t N, typename... Ts>
  struct ForwardTupleGetter : public ForwardTupleGetHelper<N, Ts...> {
    static_assert(N < sizeof...(Ts), "get subscript out of bounds");
  };

  template <Tag Target, typename... Ts>
  struct ForwardTupleFinder;

  template <Tag Target, typename First, typename... Rest>
  struct ForwardTupleFinder<Target, First, Rest...>
  {
    static constexpr const auto& find(const ForwardTuple<First, Rest...>& tuple) {
      return ForwardTupleFinder<Target, Rest...>::find(tuple.rest());
    }
  };

  template <Tag Target, typename First, typename... Rest>
  struct ForwardTupleFinder<Target, TaggedItem<Target, First>, Rest...>
  {
    static constexpr const First& find(
        const ForwardTuple<TaggedItem<Target, First>, Rest...>& tuple) {
      return tuple.item;
    }
  };

  template <Tag Target>
  struct ForwardTupleFinder<Target>
  {
    static_assert(sizeof(Target) == 0, "Target not Found in ForwardTuple");

    static constexpr void find(
        const auto& tuple) {
    }
  };

} // namespace details

template <typename First, typename... Rest>
template <size_t N>
constexpr const auto& ForwardTupleBase<First, Rest...>::get() const {
  return details::ForwardTupleGetter<N, First, Rest...>::get(*this);
}

template <Tag FirstTag, typename First, typename... Rest>
template <Tag Target>
constexpr const auto&
ForwardTuple<TaggedItem<FirstTag, First>, Rest...>::find(Target) const {
  return details::ForwardTupleFinder<Target, TaggedItem<FirstTag, First>, Rest...>::
    find(*this);
}

} // Meta

#endif // FORWARD_TUPLE_H
