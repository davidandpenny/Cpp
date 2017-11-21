#include "../Sequence.h"

#include <type_traits>

using Meta::Sequence;
using std::is_same;

namespace {

// Sample types.
  using nul = Sequence<>;
  using one = Sequence<int>;
  using i12 = Sequence<char, int>;
  using abc = Sequence<nul, one, i12>;

// is<>
  static_assert(nul::is<Sequence<>>(), "type match");
  static_assert(one::is<Sequence<int>>(), "type match");
  static_assert(i12::is<Sequence<char, int>>(), "type match");
  static_assert(abc::is<Sequence<nul, one, i12>>(), "type match");

// is<> failure cases
  static_assert(!nul::is<Sequence<int>>(), "type mismatch");
  static_assert(!one::is<Sequence<>>(), "value mismatch");
  static_assert(!nul::is<one>(), "type mismatch");
  static_assert(!abc::is<int>(), "type mismatch");

// ==
  static_assert(nul{} == Sequence<>{}, "equal");
  static_assert(one{} == Sequence<int>{}, "equal");
  static_assert(i12{} == Sequence<char, int>{}, "equal");
  static_assert(abc{} == Sequence<nul, one, i12>{}, "equal");

// !=
  static_assert(nul{} != Sequence<int>{}, "not equal");
  static_assert(one{} != Sequence<char, int>{}, "not equal");
  static_assert(i12{} != one{}, "not equal");
  static_assert(abc{} != i12{}, "not equal");

// size
  static_assert(nul::size() == 0, "empty sequence has size 0");
  static_assert(one::size() == 1, "unary sequence has size 1");
  static_assert(i12::size() == 2, "binary sequence has size 2");
  static_assert(abc::size() == 3, "tertiary sequence has size 3");

// empty
  static_assert( nul::empty(), "empty sequence is empty");
  static_assert(!one::empty(), "unary sequence isn't empty");
  static_assert(!i12::empty(), "binary sequence isn't empty");
  static_assert(!abc::empty(), "tertiary sequence isn't empty");

// front
//static_assert(nul::front(), "empty sequence has no front");
  static_assert(is_same<one::front, int>(), "unary sequence front matches");
  static_assert(is_same<i12::front, char>(), "binary sequence front matches");
  static_assert(abc::front::is<nul>(), "tertiary sequence front matches");

// pop_front<>
//static_assert(nul::pop_front, "‘pop_front’ is not a member of ‘nul’");
  static_assert(one::pop_front{} == nul{}, "pop_front matches");
  static_assert(i12::pop_front{} == Sequence<int>{}, "pop_front matches");
  static_assert(abc::pop_front{} == Sequence<one, i12>{}, "pop_front matches");

// pop_back<>
//static_assert(nul::pop_back, "empty sequence has no pop_back");
  static_assert(one::pop_back{} == nul{},
      "pop_back matches");
  static_assert(i12::pop_back{} == Sequence<char>{},
      "pop_back matches");
  static_assert(abc::pop_back{} == Sequence<nul, one>{},
      "pop_back matches");

// push_front<>
  static_assert(nul::push_front<int>{} == one{},
      "push_front matches");
  static_assert(one::push_front<char>{} == i12{},
      "push_front matches");
  static_assert(i12::push_front<double>{} == Sequence<double, char, int>{},
      "push_front matches");
  static_assert(abc::push_front<abc>{} == Sequence<abc, nul, one, i12>{},
      "push_front matches");

// push_back<>
  static_assert(nul::push_back<int>{} == one{}, "push_back matches");
  static_assert(one::push_back<char>{} == Sequence<int, char>{},
      "push_back matches");
  static_assert(i12::push_back<double>{} == Sequence<char, int, double>{},
      "push_back matches");
  static_assert(abc::push_back<abc>{} == Sequence<nul, one, i12, abc>{},
      "push_back matches");

// append<>
  static_assert(nul::append<nul>{} == nul{}, "append matches");
  static_assert(one::append<nul>{} == one{}, "push_back matches");
  static_assert(nul::append<one>{} == one{}, "append matches");
  static_assert(one::append<nul>{} == one{}, "push_back matches");
  static_assert(abc::append<i12>{} == Sequence<nul, one, i12, char, int>{},
      "append matches");

// get()
//nul::get<0>{}; // "get subscript out of bounds";
  static_assert(is_same<one::get<0>, int>(), "unary sequence get<0> matches");
  static_assert(is_same<i12::get<0>, char>(), "binary sequence get<0> matches");
  static_assert(abc::get<0>{} == nul{}, "tertiary sequence get<0> matches");

//nul::get<1>{}; // "get subscript out of bounds";
//one::get<2>{}; // "get subscript out of bounds";
  static_assert(is_same<i12::get<1>, int>(), "binary sequence get<1> matches");
  static_assert(abc::get<1>{} == one{}, "tertiary sequence get<1> matches");

//nul::get<2>{}; // "get subscript out of bounds";
//one::get<2>{}; // "get subscript out of bounds";
  static_assert(abc::get<2>{} == i12{}, "tertiary sequence get<2> matches");

//nul::get<3>; // "get subscript out of bounds";
//one::get<3>; // "get subscript out of bounds";
//i12::get<3>; // "get subscript out of bounds";
//abc::get<3>; // "get subscript out of bounds";

// back()
//nul::back; // "back’ in ‘Sequence<>’ does not name a type";
  static_assert(is_same<one::back, int>(), "unary sequence back matches");
  static_assert(is_same<i12::back, int>(), "binary sequence back matches");
  static_assert(abc::back{} == i12{}, "tertiary sequence back matches");
}
