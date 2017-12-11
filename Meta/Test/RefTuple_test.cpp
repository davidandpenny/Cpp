#include "../RefTuple.h"

using namespace Meta::literals;
using Meta::RefTuple;

namespace {

  constexpr auto x {"first"_a}; 

  constexpr int y { 66 };

  constexpr auto z {x = y};
  constexpr auto q {z.item};

  static_assert(std::is_same<decltype(q), const int>::value, "tagged an int");
}

namespace {

  using Nul = RefTuple<>;
  using Int = RefTuple<int>;
  using IntDouble = RefTuple<int, double>;

  constexpr Nul nul;
  constexpr const int i42 {42};
  constexpr const double d66 {66.0};
  constexpr const Int i {i42};
  constexpr const IntDouble id {i42, d66};

//auto a {nul.get<0>()}; // Cannot get<> from empty RefTuple

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
