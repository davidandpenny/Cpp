#include "../Vector.h"

using Meta::Vector;

namespace {

// Sample types.
  using nul = Vector<char>;
  using one = Vector<int, 1>;
  using i12 = Vector<int, 1, 2>;
  using abc = Vector<char, 'a', 'b', 'c'>;

// is<>
  static_assert(nul::is<Vector<char>>(), "type match");
  static_assert(one::is<Vector<int, 1>>(), "type match");
  static_assert(i12::is<Vector<int, 1, 2>>(), "type match");
  static_assert(abc::is<Vector<char, 'a', 'b', 'c'>>(), "type match");

// is<> failure cases
  static_assert(!nul::is<Vector<int>>(), "type mismatch");
  static_assert(!one::is<Vector<int, 2>>(), "value mismatch");
  static_assert(!nul::is<one>(), "type mismatch");
  static_assert(!abc::is<int>(), "type mismatch");

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
  static_assert(one::front() == 1, "unary sequence front matches");
  static_assert(i12::front() == 1, "binary sequence front matches");
  static_assert(abc::front() == 'a', "tertiary sequence front matches");

// pop_front<>
//static_assert(nul::pop_front, "empty sequence has no pop_front");
  static_assert(one::pop_front::is<Vector<int>>(),
      "pop_front matches");
  static_assert(i12::pop_front::is<Vector<int, 2>>(),
      "pop_front matches");
  static_assert(abc::pop_front::is<Vector<char, 'b', 'c'>>(),
      "pop_front matches");

// pop_back<>
//static_assert(nul::pop_back, "empty sequence has no pop_back");
  static_assert(one::pop_back::is<Vector<int>>(),
      "pop_back matches");
  static_assert(i12::pop_back::is<Vector<int, 1>>(),
      "pop_back matches");
  static_assert(abc::pop_back::is<Vector<char, 'a', 'b'>>(),
      "pop_back matches");

// push_front<>
  static_assert(nul::push_front<'x'>::is<Vector<char, 'x'>>(),
      "push_front matches");
  static_assert(one::push_front<0>::is<Vector<int, 0, 1>>(),
      "push_front matches");
  static_assert(i12::push_front<0>::is<Vector<int, 0, 1, 2>>(),
      "push_front matches");
  static_assert(abc::push_front<'x'>::is<Vector<char, 'x', 'a', 'b', 'c'>>(),
      "push_front matches");

// push_back<>
  static_assert(nul::push_back<'x'>::is<Vector<char, 'x'>>(),
      "push_back matches");
  static_assert(one::push_back<2>::is<Vector<int, 1, 2>>(),
      "push_back matches");
  static_assert(i12::push_back<3>::is<Vector<int, 1, 2, 3>>(),
      "push_back matches");
  static_assert(abc::push_back<'d'>::is<Vector<char, 'a', 'b', 'c', 'd'>>(),
      "push_back matches");

// append<>
  static_assert(nul::append<nul>::is<Vector<char>>(),
      "append matches");
  /*
  static_assert(one::push_back<2>::is<Vector<int, 1, 2>>(),
      "push_back matches");
  static_assert(i12::push_back<3>::is<Vector<int, 1, 2, 3>>(),
      "push_back matches");
  static_assert(abc::push_back<'d'>::is<Vector<char, 'a', 'b', 'c', 'd'>>(),
      "push_back matches");
*/
// get()
//static_assert(nul::get<0>(), "empty sequence has no get<0>");
  static_assert(one::get<0>() == 1, "unary sequence get<0> matches");
  static_assert(i12::get<0>() == 1, "binary sequence get<0> matches");
  static_assert(abc::get<0>() == 'a', "tertiary sequence get<0> matches");

//static_assert(nul::get<1>(), "empty sequence has no get<1>");
//static_assert(one::get<1>(), "unary sequence has no get<1>");
  static_assert(i12::get<1>() == 2, "binary sequence get<1> matches");
  static_assert(abc::get<1>() == 'b', "tertiary sequence get<1> matches");

//static_assert(nul::get<2>(), "empty sequence has no get<2>");
//static_assert(one::get<2>(), "unary sequence has no get<2>");
//static_assert(i12::get<2>(), "binary sequence has no get<2>");
  static_assert(abc::get<2>() == 'c', "tertiary sequence get<2> matches");

//static_assert(nul::get<3>(), "empty sequence has no get<3>");
//static_assert(one::get<3>(), "unary sequence has no get<3>");
//static_assert(i12::get<3>(), "binary sequence has no get<3>");
//static_assert(abc::get<3>(), "tertiary sequence has no get<3>");

// back()
//static_assert(nul::back(), "empty sequence has no back");
  static_assert(one::back() == 1, "unary sequence back matches");
  static_assert(i12::back() == 2, "binary sequence back matches");
  static_assert(abc::back() == 'c', "tertiary sequence back matches");
}
