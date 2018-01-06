#include "../Tag.h"

using namespace Meta::literals;

namespace Tag_test {

  constexpr int y { 66 };

  constexpr auto z {"first"_a = y};
//constexpr auto zz {"first"_a = 1}; // TODO
  constexpr auto q {z.item};

  static_assert(std::is_same<decltype(q), const int>::value, "tagged an int");

  using Tag = decltype(z)::Tag;
  static_assert(Tag{} == "first"_a);
  static_assert(!(Tag{} == "second"_a));
}
