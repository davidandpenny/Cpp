#include <cstddef> // for size_t.
#include <type_traits>

namespace Meta {

using std::size_t;

// Sequence is a linear compiletime container of types, essentially a deque.
// It cannot hold values directly, but can hold types such as String<'h', 'i'>,
// Int<42>, or Char<'x'>.

template <typename... Ts>
struct Sequence;

namespace details {

  template <size_t N, typename... Ts>
  struct SequenceGetter;

  template <typename S1, typename S2>
  struct SequenceAppender;

  template <typename Out, typename... Ts>
  struct SequenceBackPopper;

  template <typename... Ts>
  struct SequenceBase
  {
    template <typename T>
    using push_back = Sequence<Ts..., T>;

    template <typename T>
    using push_front = Sequence<T, Ts...>;

    template <typename S>
    using append = typename SequenceAppender<Sequence<Ts...>, S>::type;

    static constexpr size_t size() { return sizeof...(Ts); }
    static constexpr bool empty()  { return size() == 0; }

    template <typename U>
    static constexpr bool is() {
      return std::is_same<U, Sequence<Ts...>>::value;
    }

    template <size_t N>
    using get = typename SequenceGetter<N, Ts...>::get;
  };

  template <typename... Ts_1, typename... Ts_2>
  struct SequenceAppender<Sequence<Ts_1...>, Sequence<Ts_2...>>
  {
    using type = Sequence<Ts_1..., Ts_2...>;
  };

  template <size_t N, typename... Ts>
  struct SequenceGetHelper;

  template <size_t N, typename T, typename... Ts>
  struct SequenceGetHelper<N, T, Ts...>
  {
    using get = typename SequenceGetHelper<N-1, Ts...>::get;
  };

  template <typename T, typename... Ts>
  struct SequenceGetHelper<0, T, Ts...>
  {
    using get = T;
  };

  template <size_t N>
  struct SequenceGetHelper<N>
  {
    using get = Sequence<>; // just to minimize errors.
  };

  template <size_t N, typename... Ts>
  struct SequenceGetter : SequenceGetHelper<N, Ts...>
  {
    static_assert(N < sizeof...(Ts), "get subscript out of bounds");
  };

  template <typename... Fronts, typename T, typename... Backs>
  struct SequenceBackPopper<Sequence<Fronts...>, T, Backs...>
  {
    using type = typename
      SequenceBackPopper<Sequence<Fronts..., T>, Backs...>::type;
  };

  template <typename... Fronts, typename Back>
  struct SequenceBackPopper<Sequence<Fronts...>, Back>
  {
    using type = Sequence<Fronts...>;
  };
} // namespace details

template <>
struct Sequence<>
  : public details::SequenceBase<>
{};

template <typename T>
struct Sequence<T>
 : public details::SequenceBase<T>
{
  using front = T;
  using back = T;

  using pop_front = Sequence<>;
  using pop_back = Sequence<>;
};

template <typename T, typename... Rest>
struct Sequence<T, Rest...>
 : public details::SequenceBase<T, Rest...>
{
  using front = T;

  using back =
    typename details::SequenceGetter<sizeof...(Rest), T, Rest...>::get;

  using pop_front = Sequence<Rest...>;

  using pop_back = 
    typename details::SequenceBackPopper<Sequence<>, T, Rest...>::type;
};

template<typename... T1s, typename... T2s>
constexpr bool
  operator==(const Sequence<T1s...>&, const Sequence<T2s...>&)
{
  return false;
}

template<typename... Ts>
constexpr bool
  operator==(const Sequence<Ts...>&, const Sequence<Ts...>&)
{
  return true;
}

template<typename... T1s, typename... T2s>
constexpr bool
  operator!=(const Sequence<T1s...>& s1, const Sequence<T2s...>& s2)
{
  return !(s1 == s2);
}

} // Meta

