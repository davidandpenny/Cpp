#include "../String.h"

#include <cstring>

using Meta::String;
using Meta::operator""_S;

namespace {

// Sample strings.
  using nul = String<char>;
  using abc = String<char, 'a', 'b', 'c'>;

// is<>
  static_assert(nul::is<String<char>>(), "type match");
  static_assert(abc::is<String<char, 'a', 'b', 'c'>>(), "type match");

  static_assert(""_S.is<nul>(), "type match");
  static_assert("abc"_S.is<abc>(), "type match");

// ==
  static_assert(""_S == nul{}, "equality works");
  static_assert("abc"_S == abc{}, "equality works");

//static_assert(L""_S == nul{}, "mismatched types");

  static_assert(!(""_S == abc{}), "equality works");
  static_assert(!("abc"_S == nul{}), "equality works");

  static_assert(""_S == ""_S, "equality works");
  static_assert("abc"_S == "abc"_S, "equality works");

// !=
  static_assert(""_S != abc{}, "inequality works");
  static_assert("abc"_S != nul{}, "inequality works");

  static_assert(!(""_S != nul{}), "inequality works");
  static_assert(!("abc"_S != abc{}), "inequality works");

  static_assert(""_S != "abc"_S, "inequality works");
  static_assert("abc"_S != ""_S, "inequality works");

// +
  static_assert("hello"_S + " "_S + "world"_S == "hello world"_S,
      "concatenation works");

  constexpr char hello[] {"hello"};
  constexpr char world[] {"world"};

  static_assert(hello != world, "different worlds");
  static_assert(strcmp(hello, world) != 0, "different worlds");
}
