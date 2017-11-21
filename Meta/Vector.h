#include <cstddef> // for size_t.
#include <type_traits>

namespace Meta {

using std::size_t;

template <typename T, T... items>
struct Vector;

namespace details {

  template <size_t N, typename T, T... items>
  struct VectorGetter;

  template <typename S1, typename S2>
  struct VectorAppender;

  template <typename T, typename Out, T... items>
  struct VectorBackPopper;

  template <typename T, T... items>
  struct VectorBase
  {
    template <T item>
    using push_back = Vector<T, items..., item>;

    template <T item>
    using push_front = Vector<T, item, items...>;

    template <typename S2>
    using append = typename VectorAppender<Vector<T, items...>, S2>::type;

    static constexpr size_t size() { return sizeof...(items); }
    static constexpr bool empty()  { return size() == 0; }

    template <typename U>
    static constexpr bool is() {
      return std::is_same<U, Vector<T, items...>>::value;
    }

    template <size_t N>
    static constexpr T get() {
      return VectorGetter<N, T, items...>::get();
    }
  };

  template <typename T, T... items_1, T... items_2>
  struct VectorAppender<Vector<T, items_1...>, Vector<T, items_2...>>
  {
    using type = Vector<T, items_1..., items_2...>;
  };

  template <size_t N, typename T, T item, T... items>
  struct VectorGetter<N, T, item, items...>
  {
    static constexpr T get() {
      return VectorGetter<N-1, T, items...>::get();
    }
  };

  template <typename T, T item, T... items>
  struct VectorGetter<0, T, item, items...>
  {
    static constexpr T get() {
      return item;
    }
  };

  template <size_t N, typename T>
  struct VectorGetter<N, T>
  {
    static constexpr T get() = delete;
  };

  template <typename T, T item, T... fronts, T... backs>
  struct VectorBackPopper<T, Vector<T, fronts...>, item, backs...>
  {
    using type = typename
      VectorBackPopper<T, Vector<T, fronts..., item>, backs...>::type;
  };

  template <typename T, T item, T... fronts>
  struct VectorBackPopper<T, Vector<T, fronts...>, item>
  {
    using type = Vector<T, fronts...>;
  };

} // namespace details

template <typename T>
struct Vector<T> :
public details::VectorBase<T>
{};

template <typename T, T first, T... rest>
struct Vector<T, first, rest...> :
public details::VectorBase<T, first, rest...>
{
  static constexpr T front() { return first; }
  static constexpr T back() {
    return details::VectorGetter<sizeof...(rest), T, first, rest...>::get();
  }

  using pop_front = Vector<T, rest...>;
  using pop_back = 
    typename details::VectorBackPopper<T, Vector<T>, first, rest...>::type;
};

} // Meta

