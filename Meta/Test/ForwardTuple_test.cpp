#include "../ForwardTuple.h"

#include <type_traits>

using namespace Meta::literals;
using Meta::ForwardTuple;
using std::remove_const_t;

namespace ForwardTuple_get_test { // O(0).

  using Nul = ForwardTuple<>;
  using Int = ForwardTuple<int>;
  using IntDouble = ForwardTuple<int, double>;

  constexpr Nul nul;
  constexpr const int i42 {42};
  constexpr const double d66 {66.0};
  constexpr const Int i {i42};
  constexpr const IntDouble id {i42, d66};

//auto a {nul.get<0>()}; // Cannot get<> from empty ForwardTuple

  constexpr auto b {i.get<0>()};
  static_assert(std::is_same<decltype(b), const int>::value, "b is an int");
  static_assert(b == 42, "Got b");

//auto c {i.get<1>()}; // get subscript out of bounds

  constexpr auto d {id.get<0>()};
  static_assert(std::is_same<decltype(d), const int>::value, "d is an int");
  static_assert(d == 42, "Got d");

  constexpr auto e {id.get<1>()};
  static_assert(std::is_same<decltype(e), const double>::value, "e is a double");
  static_assert(e == 66.0, "Got e");

//auto f {id.get<2>()}; // get subscript out of bounds

}

namespace ForwardTuple_find_test { // O(0)

  using Nul = ForwardTuple<>;

  Nul nul;
//auto a {nul.find("first"_a)}; // "Cannot find<> in empty ForwardTuple"

  constexpr int x { 42 };
  constexpr double y { 66.6 };
  constexpr auto z {"first"_a = x};

  using TaggedInt = ForwardTuple<remove_const_t<decltype(z)>>;
  constexpr TaggedInt w {z};

  constexpr auto c = w.find("first"_a);
  static_assert(c == 42, "Found 'first'");

//auto d = w.find<decltype("not there"_a)>(); // "Target not Found in ForwardTuple"

  constexpr auto v {L"second"_a = y};
  using TaggedIntDouble
    = ForwardTuple<remove_const_t<decltype(z)>, remove_const_t<decltype(v)>>;

  constexpr TaggedIntDouble u {z, v};
  constexpr auto e = u.find("first"_a);
  static_assert(e == 42, "Found 'first'");
  constexpr auto f = u.find(L"second"_a);
  static_assert(f == 66.6, "Found 'second'");

//auto g {u.find("notthere"_a)}; // Target not Found in ForwardTuple
//auto h {u.find("second"_a)}; // Target not Found in ForwardTuple
}

namespace ForwardTuple_cannot_be_mixed_test { // O(0)

  constexpr const int i42 {42};
  constexpr int x { 42 };
  constexpr auto z {"first"_a = x};

  using TaggedIntInt
    = ForwardTuple<remove_const_t<decltype(z)>, remove_const_t<decltype(i42)>>;

  using IntTaggedInt
    = ForwardTuple<remove_const_t<decltype(i42)>, remove_const_t<decltype(z)>>;

//constexpr TaggedIntInt w {z, x}; -- "all or no parameters must be tagged"
//constexpr IntTaggedInt v {x, z}; -- "all or no parameters must be tagged"
}
