#include "../Tag.h"

using namespace Meta::literals;

namespace TaggedInt_test {

  constexpr int y {42};

  constexpr auto z {"first"_a = y};
  constexpr auto q {z.item};

  static_assert(std::is_same<decltype(q), const int>::value, "tagged an int");

  using Tag = decltype(z)::Tag;
  static_assert(Tag{} == "first"_a);
  static_assert(!(Tag{} == "second"_a));

  static_assert(q == 42);
}

namespace TaggedIntRvalue_test {

//constexpr auto z {"first"_a = 66}; // non-constexpr.
  constexpr auto q {("first"_a = 66).item};

  static_assert(std::is_same<decltype(q), const int>::value, "tagged an int");

  static_assert(q == 66);
}
